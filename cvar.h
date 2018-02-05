#ifndef CVAR_H
#define CVAR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// this file implements a config system which reads/stores variables in ./cvars.cfg

struct cvar
{
	const char *name;
	int value;
};

static struct cvar *cvars;

#define CVAR_SCREEN_WIDTH cvars[0].value
#define CVAR_SCREEN_HEIGHT cvars[1].value
#define FULLSCREEN cvars[2].value

void generateCvarFile();

void parseCvars()
{
	FILE *cvarFile = fopen("cvars.cfg", "r");
	if(!cvarFile)
	{
		fprintf(stderr, "[parseCvars] Could not find cvars.cfg. Generating a default one.\n");
		generateCvarFile();
		return;
	}

	char buffer[256];
	while(fgets(buffer, 256, cvarFile))
	{
		char *token;
		token = strtok(buffer, "=");
		printf("[parseCvars] Found cvar \"%s\" with value ", token);
		token = strtok(NULL, "\n");
		for(unsigned i = 0; i < strlen(token); i++)
		{
			if(!isdigit(token[i]))
			printf("INVALID.");
		}
		printf("%s.\n", token);
	}
}

int getCvarValue(const char *cvar)
{
	if(!cvars) return -1;
	return 0;
}

void setCvarValue(const char *cvar, int value)
{
	if(!cvars) return;
}

void generateCvarFile()
{
	FILE *cvarFile = fopen("cvars.cfg", "w");
	if(!cvarFile)
	{
		fprintf(stderr, "[generateCvarFile] Cannot create cvars.cfg file. Is the filesystem read-only?\n");
		return;
	}
	fprintf(cvarFile,
			"screenWidth=1024\n"
			"screenHeight=768\n"
			"fullscreen=1\n");
	fclose(cvarFile);
}

void saveCvarFile()
{
	FILE *cvarFile = fopen("cvars.cfg", "w");
	if(!cvarFile)
	{
		fprintf(stderr, "[saveCvarFile] Cannot open or create cvars.cfg file. Is the filesystem read-only?\n");
		return;
	}
	for(int i = 0; ; i++)
	{
		fprintf(cvarFile, "%s=%d\n", cvars[i].name, cvars[i].value);
	}
	fclose(cvarFile);
}
#endif // CVAR_H
