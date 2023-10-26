#include <stdio.h>
#include "converte.h"

int main(void)
{
	//entradas utf8:
	FILE *eutf8 = fopen("utf8_peq.txt", "r");
	FILE *svar = fopen("var_saida", "w");

	utf2varint(eutf8, svar);

	FILE *e2utf8 = fopen("utf8_demo.txt", "r");
	FILE *s2var = fopen("var_saida2", "w");

	utf2varint(e2utf8, s2var);

	//entradas varint:
	FILE *evar = fopen("var_peq", "r");
	FILE *sutf8 = fopen("utf8_saida.txt", "w");

	varint2utf(evar, sutf8);

	FILE *e2var = fopen("var_demo", "r");
	FILE *s2utf8 = fopen("utf8_saida2.txt", "w");

	printf("%d\n", varint2utf(e2var, s2utf8));

	//fechando arquivos:
	fclose(eutf8);
	fclose(svar);
	fclose(e2utf8);
	fclose(s2var);

	fclose(evar);
	fclose(sutf8);
	fclose(e2var);
	fclose(s2utf8);
	
	return 0;
}