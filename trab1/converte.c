#include <stdio.h>
#include <stdlib.h>
#include "converte.h"

typedef union {
	unsigned char c[4];
	unsigned int i;
} utf8;

int conta_bytes(char c)
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

int limpa_utf8(utf8 u, int bytes)
{
	int k = 0;
	int aux = 0;
	for (int i = 0; i < bytes; i++)
	{
		if (i == 0){
			u.c[i] = u.c[i] << bytes;
			u.c[i] = u.c[i] >> bytes;
			aux = u.c[i];
			k += aux << (6*(bytes-1));
		}
		else{
		u.c[i] = u.c[i] << 2;
		u.c[i] = u.c[i] >> 2;
		aux = u.c[i];
		k += aux << (6*(bytes-i-1));
		}
	}
	return k;
}

utf8 separa7bits(utf8 u)
{
	utf8 aux;
	aux.i = 0;
	aux.c[0] = u.c[0] & 0x7f;
	aux.c[1] = ((u.c[1] & 0x3f) << 1) + (u.c[0] >> 7);
	aux.c[2] = ((u.c[2] & 0x1f) << 2) + (u.c[1] >> 6);
	aux.c[3] = ((u.c[3] & 0x0f) << 3) + (u.c[2] >> 5);
	return aux;
}

int conv_varint(utf8 u){
	utf8 aux;
	utf8 vint;
	vint.i = 0;
	aux = separa7bits(u);
	for (int i = 0; i < 4; i++)
	{
		if (aux.c[i] != 0)
		{
			if (i != 0)
			{
				vint.c[0] = vint.c[0] | 0x80;
				vint.i = vint.i << 8;
			}
			vint.c[0] += aux.c[i];
		}
	}
	return vint.i;
}

int utf2varint(FILE *arq_entrada, FILE *arq_saida)
{
	utf8 c;
	c.i = 0;
	c.c[0] = getc(arq_entrada);
	while (((char)c.c[0]) != EOF)
	{
		int bytes = conta_bytes(c.c[0]);
		
		fread(&c.c[1], sizeof(c.c[1]), bytes - 1, arq_entrada);
		c.i = limpa_utf8(c, bytes);
		c.i = conv_varint(c);
		for (int i = 3; i >= 0; i--)
		{
			if (c.c[i] != 0)
			{
				if (fputc(c.c[i], arq_saida) != c.c[i])
				{
					fprintf(stderr, "Erro na escrita do arquivo\n");
					return -1;
				}
			}
		}
		c.c[0] = fgetc(arq_entrada);
	}

	return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida)
{
	return 0;
}