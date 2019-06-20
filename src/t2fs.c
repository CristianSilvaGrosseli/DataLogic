
/**
*/
#include "../include/t2fs.h"
#include "../include/apidisk.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void initializeFreeBlocks();
void writeInBlock(BYTE* buffer, WORD size, WORD blockAddress);

/*-----------------------------------------------------------------------------
Função:	Informa a identificação dos desenvolvedores do T2FS.
-----------------------------------------------------------------------------*/
int identify2 (char *name, int size) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Formata logicamente o disco virtual t2fs_disk.dat para o sistema de
		arquivos T2FS definido usando blocos de dados de tamanho 
		corresponde a um múltiplo de setores dados por sectors_per_block.
-----------------------------------------------------------------------------*/
int format2 (int sectors_per_block) {
	initializeFreeBlocks();

	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para criar um novo arquivo no disco e abrí-lo,
		sendo, nesse último aspecto, equivalente a função open2.
		No entanto, diferentemente da open2, se filename referenciar um 
		arquivo já existente, o mesmo terá seu conteúdo removido e 
		assumirá um tamanho de zero bytes.
-----------------------------------------------------------------------------*/
FILE2 create2 (char *filename) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para remover (apagar) um arquivo do disco. 
-----------------------------------------------------------------------------*/
int delete2 (char *filename) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função que abre um arquivo existente no disco.
-----------------------------------------------------------------------------*/
FILE2 open2 (char *filename) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para fechar um arquivo.
-----------------------------------------------------------------------------*/
int close2 (FILE2 handle) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para realizar a leitura de uma certa quantidade
		de bytes (size) de um arquivo.
-----------------------------------------------------------------------------*/
int read2 (FILE2 handle, char *buffer, int size) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para realizar a escrita de uma certa quantidade
		de bytes (size) de  um arquivo.
-----------------------------------------------------------------------------*/
int write2 (FILE2 handle, char *buffer, int size) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para truncar um arquivo. Remove do arquivo 
		todos os bytes a partir da posição atual do contador de posição
		(current pointer), inclusive, até o seu final.
-----------------------------------------------------------------------------*/
int truncate2 (FILE2 handle) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Altera o contador de posição (current pointer) do arquivo.
-----------------------------------------------------------------------------*/
int seek2 (FILE2 handle, DWORD offset) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para criar um novo diretório.
-----------------------------------------------------------------------------*/
int mkdir2 (char *pathname) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para remover (apagar) um diretório do disco.
-----------------------------------------------------------------------------*/
int rmdir2 (char *pathname) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para alterar o CP (current path)
-----------------------------------------------------------------------------*/
int chdir2 (char *pathname) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para obter o caminho do diretório corrente.
-----------------------------------------------------------------------------*/
int getcwd2 (char *pathname, int size) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função que abre um diretório existente no disco.
-----------------------------------------------------------------------------*/
DIR2 opendir2 (char *pathname) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para ler as entradas de um diretório.
-----------------------------------------------------------------------------*/
int readdir2 (DIR2 handle, DIRENT2 *dentry) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para fechar um diretório.
-----------------------------------------------------------------------------*/
int closedir2 (DIR2 handle) {
	return -1;
}

/*-----------------------------------------------------------------------------
Função:	Função usada para criar um caminho alternativo (softlink) com
		o nome dado por linkname (relativo ou absoluto) para um 
		arquivo ou diretório fornecido por filename.
-----------------------------------------------------------------------------*/
int ln2 (char *linkname, char *filename) {
	return -1;
}

void initializeFreeBlocks()
{
	BYTE mbr[256];

	int success = read_sector(0, mbr);
	printf("read_sector success: %d\n", success);

	if(success != 0)
	{
		return;
	}

	WORD sectorSize = (mbr[3] << 8) + mbr[2];
	printf("sector's size: %u\n", sectorSize);
	
	WORD beginAddress = (mbr[11] << 24) + (mbr[10] << 16) + (mbr[9] << 8) + (mbr[8] << 0);
	WORD endAddress = (mbr[15] << 24) + (mbr[14] << 16) + (mbr[13] << 8) + (mbr[12] << 0);
	WORD numSectors = endAddress - beginAddress + 1;
	printf("First sector address: %d\n", beginAddress);
	printf("Last sector address: %d\n", endAddress);
	printf("Total sectors: %u\n", numSectors);

	WORD sectorsPerBlock = 4;
	WORD numLogicBlocks = numSectors / sectorsPerBlock;
	printf("Sectors per logic block: %d\n", sectorsPerBlock); 
	printf("Logic blocks's number: %d\n", numLogicBlocks);	

	WORD wordsPerSector = sectorSize / sizeof(WORD);
	WORD wordsPerBlock = wordsPerSector * sectorsPerBlock;
	printf("Words per sector: %d\n", wordsPerSector);
	printf("Words per block: %d\n", wordsPerBlock);

	WORD vector[wordsPerBlock];
	WORD vectorAddress = beginAddress;
	WORD numFreeBlocks = numLogicBlocks - (numLogicBlocks / wordsPerBlock + 1);
	printf("Initial free blocks's number: %d\n", numFreeBlocks);

	WORD i;
	WORD j;
	WORD blockAddress = beginAddress;
	for(i = 1, j = 1; i <= numFreeBlocks; i++, j++)
	{
		blockAddress += sectorsPerBlock;
		vector[j-1] = blockAddress;
		if(i == numFreeBlocks)
		{
			vector[j-1] = 0;
			writeInBlock((BYTE*)vector, j*sizeof(WORD), vectorAddress);
		}
		else if(j == wordsPerBlock)
		{
			writeInBlock((BYTE*)vector, j*sizeof(WORD), vectorAddress);
			vectorAddress = blockAddress;
			j = 1;
		}
	}
}

void writeInBlock(BYTE* buffer, WORD size, WORD blockAddress)
{
	WORD numSectorsToWrite = (WORD) ceil((double)size / 256.0);
	
	WORD i;
	for(i = 1; i <= numSectorsToWrite; i++)
	{
		write_sector(blockAddress + (i-1), buffer + (i-1) * 256);
	}
}
