#include <stdio.h>
#include "converte.h"

int main(void)
{
	FILE *eutf8 = fopen("utf8_peq.txt", "r");
	FILE *evar = fopen("var_peq.txt", "r");
	FILE *sutf8 = fopen("utf8_saida.txt", "w");
	FILE *svar = fopen("var_saida.txt", "w");
	utf2varint(eutf8, svar);
	varint2utf(evar, sutf8);
	fclose(eutf8);
	fclose(evar);
	fclose(sutf8);
	fclose(svar);
	return 0;
}