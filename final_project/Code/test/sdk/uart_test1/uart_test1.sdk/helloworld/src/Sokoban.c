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

/*----------------------------------------------------
 * 	�\�໡�� : �C������a�ϡAŪ����l���a�ϸ��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *	@param	Map_data	(��X)	:�n�Q�s�J��l�a�ϸ�ƪ��Ѽ�
 *	@param	init_map	(��J)	:��l�a�Ϫ���ưѼ�
 */
void Initial_Map(int Map_data[Map1_HEIGHT][Map1_WIDTH], int init_map[Map1_HEIGHT][Map1_WIDTH]){
	for (int i = 0; i < Map1_HEIGHT; i++){
    	for (int j = 0; j < Map1_WIDTH; j++){
    		Map_data[i][j] = init_map[i][j];
   		}
	}
}

/*----------------------------------------------------
 * 	�\�໡�� : �N�C��Map��ơA�q�G���}�C�ഫ���@���}�C
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *	@param	byteArray	(��X)	: �ഫ�᪺�u�@���}�C�v���a�ϸ��
 *	@param	Map_data	(��J)	: ��J���a�ϸ��
 *	@param	Game_State	(��J)	: ��J���C�����A		|| 1.[0]:�C���|������  2.[1]:�C������
 */
void MapToArray_c(u8 *byteArray, int Map_data[Map1_HEIGHT][Map1_WIDTH], int Game_State){

	u16 i,j;
	u8 asicii_zero  = '0';													//�ƭȤ�K�����ɡA�Ϊ�ASICII�ഫ

	for (i = 0; i < Map1_HEIGHT; i++) {
        for (j = 0; j < Map1_WIDTH; j++) {
            //byteArray[i * Map1_WIDTH + j] = map[i][j];
            byteArray[i * Map1_WIDTH + j] = Map_data[i][j] + asicii_zero;		//�ƭȤ�K�����ɡA�Ϊ�ASICII�ഫ
        }
    }
    //byteArray[Map1_HEIGHT * Map1_WIDTH] = game_state;
    byteArray[Map1_HEIGHT * Map1_WIDTH] = Game_State + asicii_zero;			//�ƭȤ�K�����ɡA�Ϊ�ASICII�ഫ
}

/*----------------------------------------------------
 * 	�\�໡�� : �p��|���Q�\��c�l���ت��a�Ѿl�ƶq
 *----------------------------------------------------
 * 	�ѼƩw�q :
 * 	//1	(�@���}�C��Map)
 *	@param	cnt_data	(��X)	: �p��ت��a�Ѿl�ƶq
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�@���}�C��Map)
 *
 *	//2	(�G���}�C��Map)
 *	@param	cnt_data	(��X)	: �p��ت��a�Ѿl�ƶq
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�G���}�C��Map)
 */
/*
//1
int Remaining_Destinations(u8 *Map_data){
    u16 i;
    u8 asicii_zero  = '0';
    int cnt_data = 0;

    for(i=0; i<(Map1_HEIGHT * Map1_WIDTH); i++){
    	//if(Map_data[i] == 4){
    	if(Map_data[i] == (4+asicii_zero)){
    		cnt_data = cnt_data + 1;
    	}
    }
    //printf("\nBox : %d",cnt_data);
    return cnt_data;
}
*/
//2
void Remaining_Destinations_v(int *Remaining_Destinations_Total, int Map_data[Map1_HEIGHT][Map1_WIDTH]){
    u16 i,j;
    int cnt_data = 0;

    for(i=0; i<(Map1_HEIGHT); i++){
    	for(j=0; j<(Map1_WIDTH); j++){
    		if(Map_data[i][j] == 4){
    			cnt_data = cnt_data + 1;
    		}
    	}
    }
    *Remaining_Destinations_Total = cnt_data;
    //printf("\nBox : %d",cnt_data);
}
/*
int Remaining_Destinations(int Map_data[Map1_HEIGHT][Map1_WIDTH]){
    u16 i,j;
    int cnt_data = 0;

    for(i=0; i<(Map1_HEIGHT); i++){
    	for(j=0; j<(Map1_WIDTH); j++){
    		if(Map_data[i][j] == 3){
    			cnt_data = cnt_data + 1;
    		}
    	}
    }
    //printf("\nBox : %d",cnt_data);
    return cnt_data;
}
 */

/*----------------------------------------------------
 * 	�\�໡�� : �P�_�C�����ت��a�O�_�����Q�\��A�çP�_�C���O�_�q��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 * 	//1	(�@���}�C��Map)
 *	@param	true		(��X)	: �c�l�����\��b�ت��a�W
 *	@param	false		(��X)	: �c�l�u�|���v�����\��b�ت��a�W
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�@���}�C��Map)
 *
 *	//2	(�G���}�C��Map)
 *	@param	true		(��X)	: �c�l�����\��b�ت��a�W
 *	@param	false		(��X)	: �c�l�u�|���v�����\��b�ت��a�W
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�G���}�C��Map)
 */
//1
/*
bool isWinner(u8 *Map_data){
    u16 i;
    u8 asicii_zero  = '0';
	for(int i = 0; i < (Map1_HEIGHT*Map1_WIDTH); i++){
		if(Map_data[i] == (3+asicii_zero)){
			return false;
		}
	}
	return true;
}
 */
//2
bool isWinner(int Map_data[Map1_HEIGHT][Map1_WIDTH]){
	for(int i = 0; i < Map1_HEIGHT; i++){
		for(int j = 0; j < Map1_WIDTH; j++){
			if(Map_data[i][j] == 4){
				return false;
			}
		}
	}
	return true;
}

/*----------------------------------------------------
 * 	�\�໡�� : ���ѵ�UART�ǿ骺�C�����A�P�_
 * 	�\��ʥ� : �C���q����ݭn�A�����U���s�C�����A�~�|���ܦ��u1�v
 *----------------------------------------------------
 * 	�ѼƩw�q :
 * 	//1	(�@���}�C��Map)
 *	@param	Game_State	(��X)	: �C�����A�P�_�����G		|| 1.[0]:�C���|������  2.[1]:�C������
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�@���}�C��Map)
 *
 *	//2	(�G���}�C��Map)
 *	@param	Game_State	(��X)	: �C�����A�P�_�����G		|| 1.[0]:�C���|������  2.[1]:�C������
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�G���}�C��Map)
 */
//void Judge_Game_State(int Game_State, u8 *Map_data){

//}

void Judge_Game_State(int *Sokoban_Game_State, int Map_data[Map1_HEIGHT][Map1_WIDTH]){
	u16 i,j;
	int State_Result = 0;

	for(i=0; i<Map1_HEIGHT; i++){
		for(j=0; j<Map1_WIDTH; j++){
			if(Map_data[i][j] == 4){
				State_Result = 1;
				break;
			}
		}
		if(State_Result){
			break;
		}
	}
	*Sokoban_Game_State = State_Result? 0 : 1;

}

/*----------------------------------------------------
 * 	�b�u�G���}�C�v��Map���M��H���y��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *	@param	X			(��X)	: �H���b���uWidth�v����m
 *	@param	Y			(��X)	: �H���b���uHeight�v����m
 *	@param	Map_data	(��J)	: ��J���a�ϸ��(�G���}�C��Map)
 */
void Find_Person_Coordinates(int *X, int *Y, int Map_data[Map1_HEIGHT][Map1_WIDTH]){
	u16 i,j;
	int X_Coordinate;
	int Y_Coordinate;

	for(i=0; i<Map1_HEIGHT; i++){
		for(j=0; j<Map1_WIDTH; j++){
			if(Map_data[i][j]==5 || Map_data[i][j]==8){
				X_Coordinate = j;
				Y_Coordinate = i;
				break;
			}
		}
	}
	*X = X_Coordinate;
	*Y = Y_Coordinate;
	//printf("Person_Coordinate is X:[%d] Y:[%d]\n",X_Coordinate, Y_Coordinate);
}

/*----------------------------------------------------
 * 	�ϥΪ̫��U���s�ɡA�C������X�������\��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 */
void Player_Control(int Map_data[Map1_HEIGHT][Map1_WIDTH]){

}

/*----------------------------------------------------
 *	���s�\��->�H���V�u�W�v���ʮɡA��s�a�ϸ��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *  @param	Map_Updata	(��J||��X)	: ��s�᪺�Ϥ��e
 *	@param	Person_X	(��J)		: �H���b���uHeight�v����m
 *	@param	Person_Y	(��J)		: �H���b���uHeight�v����m
 */
void Move_Up(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y){
	if(Map_Update[Person_Y-1][Person_X]==0 || Map_Update[Person_Y-1][Person_X]==3){
		Map_Update[Person_Y-1][Person_X]+=5;
		Map_Update[Person_Y][Person_X]-=5;
	}
	else if((Map_Update[Person_Y-1][Person_X]==4 || Map_Update[Person_Y-1][Person_X]==7) && (Map_Update[Person_Y-2][Person_X]!=1) && (Map_Update[Person_Y-2][Person_X]!=4)){
		Map_Update[Person_Y-2][Person_X]+=4;
		Map_Update[Person_Y-1][Person_X]+=1;
		Map_Update[Person_Y][Person_X]-=5;
	}
}

/*----------------------------------------------------
 *	���s�\��->�H���V�u�U�v���ʮɡA��s�a�ϸ��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *  @param	Map_Updata	(��J||��X)	: ��s�᪺�Ϥ��e
 *	@param	Person_X	(��J)		: �H���b���uHeight�v����m
 *	@param	Person_Y	(��J)		: �H���b���uHeight�v����m
 */
void Move_Down(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y){
	if(Map_Update[Person_Y+1][Person_X]==0 || Map_Update[Person_Y+1][Person_X]==3){
		Map_Update[Person_Y+1][Person_X]+=5;
		Map_Update[Person_Y][Person_X]-=5;
	}else if((Map_Update[Person_Y+1][Person_X]==4 || Map_Update[Person_Y+1][Person_X]==7) && (Map_Update[Person_Y+2][Person_X]!=1) && (Map_Update[Person_Y+2][Person_X]!=4)){
		Map_Update[Person_Y+2][Person_X]+=4;
		Map_Update[Person_Y+1][Person_X]+=1;
		Map_Update[Person_Y][Person_X]-=5;
	}
}

/*----------------------------------------------------
 *	���s�\��->�H���V�u�k�v���ʮɡA��s�a�ϸ��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *  @param	Map_Updata	(��J||��X)	: ��s�᪺�Ϥ��e
 *	@param	Person_X	(��J)		: �H���b���uHeight�v����m
 *	@param	Person_Y	(��J)		: �H���b���uHeight�v����m
 */
void Move_Right(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y){
	printf("Person_X = %d  Person_Y = %d\n", Person_X, Person_Y);
	if(Map_Update[Person_Y][Person_X+1]==0 || Map_Update[Person_Y][Person_X+1]==3){
		Map_Update[Person_Y][Person_X+1]+=5;
		Map_Update[Person_Y][Person_X]-=5;
	}
	else if((Map_Update[Person_Y][Person_X+1]==4 || Map_Update[Person_Y][Person_X+1]==7) && (Map_Update[Person_Y][Person_X+2]!=1) && (Map_Update[Person_Y][Person_X+2]!=4)){
		Map_Update[Person_Y][Person_X+2]+=4;
		Map_Update[Person_Y][Person_X+1]+=1;
		Map_Update[Person_Y][Person_X]-=5;
	}
}

/*----------------------------------------------------
 *	���s�\��->�H���V�u�k�v���ʮɡA��s�a�ϸ��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 *  @param	Map_Updata	(��J||��X)	: ��s�᪺�Ϥ��e
 *	@param	Person_X	(��J)		: �H���b���uHeight�v����m
 *	@param	Person_Y	(��J)		: �H���b���uHeight�v����m
 */
void Move_Left(int Map_Update[Map1_HEIGHT][Map1_WIDTH], int Person_X, int Person_Y){
	printf("Person_X = %d  Person_Y = %d\n", Person_X, Person_Y);
	if(Map_Update[Person_Y][Person_X-1]==0||Map_Update[Person_Y][Person_X-1]==3){
		Map_Update[Person_Y][Person_X-1]+=5;
		Map_Update[Person_Y][Person_X]-=5;

	}
	else if((Map_Update[Person_Y][Person_X-1]==4||Map_Update[Person_Y][Person_X-1]==7)&&(Map_Update[Person_Y][Person_X-2]!=1)&&(Map_Update[Person_X-2][Person_X]!=4)){
		Map_Update[Person_Y][Person_X-2]+=4;
		Map_Update[Person_Y][Person_X-1]+=1;
		Map_Update[Person_Y][Person_X]-=5;
	}
}

/*----------------------------------------------------
 *	���s�\��->���s�C����l�Ʀa��
 *----------------------------------------------------
 * 	�ѼƩw�q :
 */
void Game_Reset(int Map_data[Map1_HEIGHT][Map1_WIDTH], int init_map[Map1_HEIGHT][Map1_WIDTH]){
	for (int i = 0; i < Map1_HEIGHT; i++){
    	for (int j = 0; j < Map1_WIDTH; j++){
    		Map_data[i][j] = init_map[i][j];
   		}
	}
}

//----------------------------------------------------
//�ˬdUART�ǿ骺�a�ϸ��-(�̫�ݭn�R��)
//----------------------------------------------------
void Print_Map_Data(u8 *Map_data){
	u16 i;
	for (i = 0; i < ((Map1_HEIGHT * Map1_WIDTH)+1); i++) {
		if(i == ((Map1_HEIGHT * Map1_WIDTH)+1)){
			printf("Over!");
		}else{
			printf("Map_data[%u]  Data:[%d]\n",(i), Map_data[i]);
		}
	}
}
