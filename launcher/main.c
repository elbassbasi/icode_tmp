/*
 ============================================================================
 Name        : launcher.c
 Author      : EL BASSBASI
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

extern int IManagersStart(int argc, char **argv);
int main(int argc, char* argv[]) {
	return IManagersStart(argc,argv);
}
