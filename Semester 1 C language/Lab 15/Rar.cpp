#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

void print(char *archname) {
	FILE *f = fopen(archname, "rb");
	char buffer[8];
	fread(buffer, 1, 8, f);

	int i = 0;
	long long count = 0;
	while (i < 8) {
		count += buffer[i] * powl(256, i);
		i++;
	}

	while (count != 0) {
		char *filename = (char*)malloc(20 * sizeof(char));;
		long long size = 0;
		char buff[8];
		fread(filename, 1, 20, f);
		fread(buff, 1, 8, f);

		int t = 0;
		while (t < 8) {
			size += buff[t] * powl(256, t);
			t++;
		}

		fseek(f, size, SEEK_CUR);
		fputs(filename, stdout);
		printf("\n");
		count--;
	}
}

void extracting(char *archname) {
	FILE *f = fopen(archname, "rb");
	char buffer[8];
	fread(buffer, 1, 8, f);

	int i = 0;
	long long count = 0;
	while (i < 8) {
		count += buffer[i] * powl(256, i);
		i++;
	}

	while (count != 0) {
		char filename[20] = { 0 };
		long long size = 0;
		char buff[8];

		fread(&filename, 1, 20, f);
		FILE *nf = fopen(filename, "ab");

		fread(&buff, 1, 8, f);

		int t = 0;
		while (t < 8) {
			size += buff[t] * powl(256, t);
			t++;
		}

		char *bites = (char*)malloc(sizeof(char)*size);
		fread(bites, 1, size * sizeof(char), f);
		fwrite(bites, 1, size * sizeof(char), nf);

		fclose(nf);
		count--;
	}

	fclose(f);
}

long long getFileSize(const char* file_name) {
	long long file_size = 0;
	FILE* f = fopen(file_name, "rb");
	if (f == NULL) {
		file_size = -1;
	}
	else {
		fseek(f, 0, SEEK_END);
		file_size = ftell(f);
		fclose(f);
	}
	return file_size;
}

void creating(int argc, char *argv[], char *namearch, int idx) {
	//name, size, file
	int i = idx;

	FILE *nf = fopen(namearch, "ab");
	long long temp = argc - 4;
	fwrite(&temp, sizeof(long long), 1, nf);

	while (i < argc) {
		FILE *f = fopen(argv[i], "rb");

		fwrite(argv[i], 1, 20, nf);

		long long size = getFileSize(argv[i]);
		fwrite(&size, sizeof(long long), 1, nf);

		char tmp[1000];
		int cnt;
		fseek(f, 0, SEEK_SET);
		while (!feof(f)) {
			cnt = fread(&tmp, 1, 1000 * sizeof(char), f);
			fwrite(&tmp, 1, cnt * sizeof(char), nf);
		}

		fclose(f);
		remove(argv[i]);
		i++;
	}

	fclose(nf);
}

int main(int argc, char *argv[]) {
	int create = 1;
	int extract = 0;
	int list = 0;
	char *namearch = (char*)malloc(sizeof(char)*20);
	int idx = 4;

	for (int i = 3; i < argc; i++) {
		if (!strcmp("--file", argv[1]))
			namearch = argv[2];
		if (!strcmp("--create", argv[i])) {
			create = 1;
			idx = i + 1;
		}
		if (!strcmp("--extract", argv[i]))
			extract = 1;
		if (!strcmp("--list", argv[i]))
			list = 1;
	}

	if (create) {
		creating(argc, argv, namearch, idx);
	}

	if (extract) {
		extracting(namearch);
	}

	if (list) {
		print(namearch);
	}

	return 0;
}
