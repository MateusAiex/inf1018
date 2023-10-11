#include <stdio.h>
#include <stdlib.h>
#include "converte.h"

/*
Union usada para poder acessar os bytes de um inteiro e conseguir usar shifts em todos os bits.
*/
typedef union I_C
{
	unsigned char c[4];
	unsigned int i;
} i_c;

/*
Função para contar quantos bytes tem um caractere UTF-8 a partir do primeiro byte.
*/
int conta_bytes_utf8(char c)
{
	// 11110xxx
	if ((c & 0xf0) == 0xf0)
	{
		return 4;
	}
	// 1110xxxx
	else if ((c & 0xe0) == 0xe0)
	{
		return 3;
	}
	// 110xxxxx
	else if ((c & 0xc0) == 0xc0)
	{
		return 2;
	}
	// 0xxxxxxx
	else
	{
		return 1;
	}
}

/*
Função para limpar o bits de controle de um caractere UTF-8.
*/
int limpa_utf8(i_c u, int bytes)
{
	int k = 0;	 // variável para armazenar o inteiro sem os bits de controle
	int aux = 0; // variável auxiliar para manipular os bits de u sem alterar u

	for (int i = 0; i < bytes; i++)
	{
		// caso do primeiro byte onde os bits de controle representam a quantidade de bytes do caractere
		if (i == 0)
		{
			// operações para zerar os "bytes" primeiros bits de u.c[i]
			u.c[i] = u.c[i] << bytes;
			u.c[i] = u.c[i] >> bytes;

			aux = u.c[i];
			// shift para delocar os bits necessários para o restante de u
			k += aux << (6 * (bytes - 1));
		}
		else
		{
			// operações para zerar os 2 primeiros bits de u.c[i]
			u.c[i] = u.c[i] << 2;
			u.c[i] = u.c[i] >> 2;

			aux = u.c[i];
			k += aux << (6 * (bytes - i - 1));
		}
	}
	return k;
}

/*
Função para dividir em grupos de 7 bits um inteiro de 32 bits com o primeiro bit de cada grupo igual a 0.
*/
i_c separa7bits(i_c u)
{
	i_c aux;
	aux.i = 0;
	aux.c[0] = u.c[0] & 0x7f; // zerei o primeiro bit de u.c[0]
	// zerei os 2 primeiros bits e shiftei 1 para esquerda para colocar o primeiro bit do byte anterior
	aux.c[1] = ((u.c[1] & 0x3f) << 1) + (u.c[0] >> 7);
	aux.c[2] = ((u.c[2] & 0x1f) << 2) + (u.c[1] >> 6);
	aux.c[3] = ((u.c[3] & 0x0f) << 3) + (u.c[2] >> 5);
	return aux;
}

/*
Função para converter um número para o formato varint.
*/
int conv_varint(i_c u)
{
	i_c aux;
	i_c vint;
	vint.i = 0;
	aux = separa7bits(u);
	for (int i = 0; i < 4; i++)
	{
		if (aux.c[i] != 0)
		{
			// if para tratar quando o varint só tem 1 byte
			if (i != 0)
			{
				// ligo o primeiro bit para sinalizar que o byte não é o último
				vint.c[0] = vint.c[0] | 0x80;
				// shift para "abrir espaço" para o próximo byte
				vint.i = vint.i << 8;
			}
			// insersão do byte no varint
			vint.c[0] += aux.c[i];
		}
	}
	return vint.i;
}

/*
Função para converter um arquivo UTF-8 para o formato varint.
*/
int utf2varint(FILE *arq_entrada, FILE *arq_saida)
{
	i_c c;
	c.i = 0;
	c.c[0] = fgetc(arq_entrada);
	if (ferror(arq_entrada))
	{
		fprintf(stderr, "Erro na leitura do arquivo\n");
		return -1;
	}

	// EOF é representado por -1, por isso é necessário o cast
	while (((char)c.c[0]) != EOF)
	{
		int bytes = conta_bytes_utf8(c.c[0]);

		// byte - 1 pois já li o primeiro byte
		if (fread(&c.c[1], sizeof(c.c[1]), bytes - 1, arq_entrada) != bytes - 1)
		{
			fprintf(stderr, "Erro na leitura do arquivo\n");
			return -1;
		}
		c.i = limpa_utf8(c, bytes);
		c.i = conv_varint(c);
		for (int i = 3; i >= 0; i--)
		{
			// não escrevo os bytes que são 0
			if (c.c[i] != 0)
			{
				if (fputc(c.c[i], arq_saida) != c.c[i])
				{
					fprintf(stderr, "Erro na escrita do arquivo\n");
					return -1;
				}
			}
		}
		// leio o próximo byte para o próximo loop
		c.c[0] = fgetc(arq_entrada);
		if (ferror(arq_entrada))
		{
			fprintf(stderr, "Erro na leitura do arquivo\n");
			return -1;
		}
	}
	return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida)
{
	return 0;
}