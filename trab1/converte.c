#include <stdio.h>
#include <stdlib.h>
#include "converte.h"

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

int utf2varint(FILE *arq_entrada, FILE *arq_saida)
{
	char c = fgetc(arq_entrada);
	while (c != EOF)
	{
		int bytes = conta_bytes(c);
		for (; bytes > 0; bytes--)
		{
			if (fwrite(&c, sizeof(c), 1, arq_saida) != 1)
			{
				fprintf(stderr, "ERROR DE ESCRITA\n");
				return 1;
			}
			c = fgetc(arq_entrada);
		}
	}

	return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida)
{
	return 0;
}