//initial head file
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>


//�w�q�a�Ϫ��e�j�p
#define Map1_HEIGHT 9
#define Map1_WIDTH	8

//�w�q�a�Ϫ��}�C��T
int init_map[Map1_HEIGHT][Map1_WIDTH] = {
	{0, 0, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 0, 0, 1, 0},
	{1, 3, 5, 4, 0, 0, 1, 0},
	{1, 1, 1, 0, 4, 3, 1, 0},
	{1, 3, 1, 1, 4, 0, 1, 0},
	{1, 0, 1, 0, 3, 0, 1, 1},
	{1, 4, 0, 0, 4, 4, 3, 1},
	{1, 0, 0, 0, 3, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};
/*
int init_map[Map1_HEIGHT][Map1_WIDTH] = {
	{0, 0, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 0, 0, 1, 0},
	{1, 3, 4, 5, 0, 0, 1, 0},
	{1, 1, 1, 0, 0, 3, 1, 0},
	{1, 3, 1, 1, 0, 0, 1, 0},
	{1, 0, 1, 0, 3, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 3, 1},
	{1, 0, 0, 0, 3, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};
int init_map[Map1_HEIGHT][Map1_WIDTH] = {
	{0, 0, 1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 0, 0, 1, 0},
	{1, 3, 5, 4, 0, 0, 1, 0},
	{1, 1, 1, 0, 4, 3, 1, 0},
	{1, 3, 1, 1, 4, 0, 1, 0},
	{1, 0, 1, 0, 3, 0, 1, 1},
	{1, 4, 0, 0, 4, 4, 3, 1},
	{1, 0, 0, 0, 3, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};
 */
/*	0:Empty Position	|	1:Game Wall		|	3:Where the box should be placed
 * 	4:Box Position		|	5:Human Position-1
*/

//Ū���̪�l���a�ϸ��
void Initial_Map(int Map_data[Map1_HEIGHT][Map1_WIDTH], int init_map[Map1_HEIGHT][Map1_WIDTH]);

//�N�C����Map��Ʊq�G���}�C�ഫ���@���}�C
void MapToArray_c(u8 *byteArray, int Map_data[Map1_HEIGHT][Map1_WIDTH], int Game_State);

//�p��ت��a�Ѿl�ƶq
//int Remaining_Destinations(u8 *Map_data); //1
//int Remaining_Destinations(int Map_data[Map1_HEIGHT][Map1_WIDTH]);//2
void Remaining_Destinations_v(int *Remaining_Destinations_Total, int Map_data[Map1_HEIGHT][Map1_WIDTH]);

//�P�_�C���O�_�ӧQ -1(�ഫ�L��map) 2(���ഫ�L��map)
//bool isWinner(u8 *Map_data);							//1
bool isWinner(int Map_data[Map1_HEIGHT][Map1_WIDTH]);	//2

//���ѵ�UART�ǿ骺�C�����A�P�_|| 1.[0]:�C���|������  2.[1]:�C������
void Judge_Game_State(int *Sokoban_Game_State, int Map_data[Map1_HEIGHT][Map1_WIDTH]);

//�b�u�G���}�C�v��Map���M��H���y��
void Find_Person_Coordinates(int *X, int *Y, int Map_data[Map1_HEIGHT][Map1_WIDTH]);

//���s�\��->�H���V�u�W�v���ʮɡA��s�a�ϸ��
void Move_Up(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y);

//���s�\��->�H���V�u�U�v���ʮɡA��s�a�ϸ��
void Move_Down(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y);

//���s�\��->�H���V�u�k�v���ʮɡA��s�a�ϸ��
void Move_Left(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y);

//���s�\��->�H���V�u�k�v���ʮɡA��s�a�ϸ��
void Move_Right(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y);

//���s�\��->���s�C���a�ϩM�C�����A
void Game_Reset(int Map_data[Map1_HEIGHT][Map1_WIDTH], int init_map[Map1_HEIGHT][Map1_WIDTH]);
//�ˬd�a�ϸ��
void Print_Map_Data(u8 *Map_data);