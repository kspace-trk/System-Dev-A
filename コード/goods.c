/*
 * �t�@�C����	: goods.c
 * �@�\			: ���i�Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  2012/02/14 V02L1
 */

/* �w�b�_�[�̎�荞�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "goods.h"

/* static�ϐ��錾 */
static GOODS *root = NULL;		/* ���i��񃊃X�g�̐擪�m�[�h�Q�Ɨp */

/* static�֐��錾 */
static void CreateGoodsList(GOODS **goods);
static int GetGoodsID(char *id);
static void SortGoodsList(const int key, const int ud);

/*
 * �֐���			: int ReadGoodsFile(GOODS **goods)
 * �@�\				: ���i�������iID���Ƀ��X�g�\���ɓǂݍ���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: GOODS **goods	:�ǂݍ��񂾏��i���̐擪�m�[�h�̃A�h���X
 * �߂�l			: int	:TRUE�i�ǂݍ��ݐ���j���TRUE��Ԃ�
 * ���L����			: ���i�R�[�h�Ń\�[�g���Ȃ����荞��
 */
int ReadGoodsFile(GOODS **goods)
{
	int retVal = TRUE;
	GOODS *newone;								/* ���i���̒ǉ��m�[�h�Q�Ɨp */
	GOODS *target;								/* �^�[�Q�b�g�m�[�h�p */
	FILE* fp;									/* �t�@�C���|�C���^ */
	char buf[GOODS_SIZE+REC_DELIMITER_SIZE];	/* �t�@�C���ǂݍ��ݗ̈�i1���R�[�h�T�C�Y���]�T����������j */
	errno_t error;
	
	/* ���i���t�@�C����ǂݍ��� */
	error = fopen_s(&fp, GOODS_FILE_NAME, "r");
	if(error != 0) {
		printf("\n���i���t�@�C��������܂���B�������I�����܂��B\n");
		exit(EXIT_FAILURE);
	}
	
	/* �t�@�C���ǂݍ��݂̂��߂̑O���� */
	CreateGoodsList(&target);
	*goods = target;
	memset(buf, '\0', sizeof(buf));								/* �t�@�C���ǂݍ��ݗ̈���N���A */
	
	/* �t�@�C����EOF�܂œǂݍ��� */
	while(fgets(buf, sizeof(buf), fp) != NULL) {				/* �t�@�C���I���܂œǂݍ��� */
		
		/* �V���ȃm�[�h��ǉ����f�[�^���i�[���� */
		if((newone = (GOODS*)malloc(sizeof(GOODS))) == NULL) {	/* �m�[�h���쐬 */
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}
		
		/* ���i�����m�[�h�Ɋi�[���� */
		strncpy_s(newone->id, GOODS_ID_SIZE+1, &buf[GOODS_ID_POS], _TRUNCATE);
		strncpy_s(newone->title, GOODS_TITLE_SIZE+1, &buf[GOODS_TITLE_POS], _TRUNCATE);
		strncpy_s(newone->genre, GOODS_GENRE_SIZE+1, &buf[GOODS_GENRE_POS], _TRUNCATE);
		strncpy_s(newone->sellDat, GOODS_SELL_DATE_SIZE+1, &buf[GOODS_SELL_DATE_POS], _TRUNCATE);
		strncpy_s(newone->rentDat, GOODS_RENT_DATE_SIZE+1, &buf[GOODS_RENT_DATE_POS], _TRUNCATE);
		strncpy_s(newone->lendMID, GOODS_LEND_MID_SIZE+1, &buf[GOODS_LEND_MID_POS], _TRUNCATE);
		strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, &buf[GOODS_LEND_STS_POS], _TRUNCATE);
		strncpy_s(newone->lendNum, GOODS_LEND_NUM_SIZE+1, &buf[GOODS_LEND_NUM_POS], _TRUNCATE);
		strncpy_s(newone->keep, GOODS_KEEP_SIZE+1, &buf[GOODS_KEEP_POS], _TRUNCATE);

		/* �����̋󔒂��폜���� */
		TrimSpace(newone->id);
		TrimSpace(newone->title);
		TrimSpace(newone->genre);
		TrimSpace(newone->sellDat);
		TrimSpace(newone->rentDat);
		TrimSpace(newone->lendMID);
		TrimSpace(newone->lendSts);
		TrimSpace(newone->lendNum);
		TrimSpace(newone->keep);
		
		/* ID�ŏ����ɂȂ�悤�Ƀm�[�h��ǉ����� */
		target = root;											/* �^�[�Q�b�g��擪�ɐݒ� */
		while(TRUE) {
			/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
			if(target->next != NULL) {
				/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
				if(strncmp(newone->id, target->next->id, GOODS_ID_SIZE) < 0) {
					newone->next = target->next;
					target->next = newone;
					break;
				} else {
					target = target->next;						/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
				}
			} else {
				/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
				newone->next = NULL;
				target->next = newone;
				break;
			}
		}
	}
	fclose(fp);
	return retVal;
}

/*
 * �֐���			: static void CreateGoodsList(GOODS **goods)
 * �@�\				: ���i��񃊃X�g������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: GOODS **goods	:�_�~�[�m�[�h�̃A�h���X
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void CreateGoodsList(GOODS **goods)
{
	/* �_�~�[�m�[�h���쐬���� */
	FreeGoodsList();
	if((root = (GOODS*)malloc(sizeof(GOODS))) == NULL) {
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	root->next = NULL;
	*goods = root;
}

/*
 * �֐���			: void FreeGoodsList(void)
 * �@�\				: ���i��񃊃X�g������������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void FreeGoodsList(void)
{
	GOODS *temp;
	
	while(root != NULL) {
		temp = root;
		root = root->next;
		free(temp);
	}
}

/*
 * �֐���			: int WriteGoodsFile(void)
 * �@�\				: ���i��񃊃X�g���t�@�C���ɏ�������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�������ݐ���j���TRUE��Ԃ�
 * ���L����			: ���i�R�[�h�Ń\�[�g���Ȃ����荞��
 */
int WriteGoodsFile(void)
{
	int retVal = TRUE;
	FILE* fp;							/* �t�@�C���|�C���^ */
	GOODS *target;						/* �^�[�Q�b�g�m�[�h�p */
	char form[WRITEGOODSFILE_BUF_SIZE];	/* �t�H�[�}�b�g�p������ */
	errno_t error;

	/* �t�@�C�����I�[�v������ */
	error = fopen_s(&fp, GOODS_FILE_NAME, "w");
	if(error != 0) {
		printf("\n���i���t�@�C���ɏ������݂ł��܂���B�������I�����܂��B\n");
		exit(EXIT_FAILURE);
	}
	
	/* fprintf�̃t�H�[�}�b�g��ݒ肷�� */
	sprintf_s(form, WRITEGOODSFILE_BUF_SIZE, "%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds%%-%ds\n",
		GOODS_ID_SIZE,
		GOODS_TITLE_SIZE,
		GOODS_GENRE_SIZE,
		GOODS_SELL_DATE_SIZE,
		GOODS_RENT_DATE_SIZE,
		GOODS_LEND_MID_SIZE,
		GOODS_LEND_STS_SIZE,
		GOODS_LEND_NUM_SIZE,
		GOODS_KEEP_SIZE
	);
	
	/* ���i��񃊃X�g���t�@�C���ɏ������� */
	target = root;
	while(target->next != NULL) {
		/* ���X�g�̓��e���������� */
		target = target->next;
		fprintf(fp, form,
			target->id,
			target->title,
			target->genre,
			target->sellDat,
			target->rentDat,
			target->lendMID,
			target->lendSts,
			target->lendNum,
			target->keep
		);
	}
	fclose(fp);
	return retVal;
}
 
/*
 * �֐���			: int SearchGoods(const char *id, GOODS **g)
 * �@�\				: �yD-1111�z�w�肵��ID�̏��i�����擾����
 * ���̓p�����[�^	: const char *id	:�������鏤�iID
 * �o�̓p�����[�^	: GOODS **g			:�������ꂽ���i���m�[�h�ւ̃|�C���^
 * �߂�l			: int	:TRUE�i���i�����擾�j/FALSE�i�w�肵�����iID���Ȃ��j
 * ���L����			: �Ȃ�
 */
int SearchGoods(const char *id, GOODS **g)
{
	int retVal = FALSE;
	GOODS *target;			/* �^�[�Q�b�g�m�[�h�p */

	target = root;
	while(target->next != NULL) {
		target = target->next;
		if(strncmp(target->id, id, GOODS_ID_SIZE) == 0) {
			*g = target;		/* �q�b�g�����f�[�^�̃A�h���X��߂�l�ɐݒ� */
			retVal = TRUE;
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: void ClearGoodsBuffer(GOODS *g)
 * �@�\				: �yD-1131�z���i���o�b�t�@���N���A����
 * ���̓p�����[�^	: GOODS *g	:���i���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void ClearGoodsBuffer(GOODS *g)
{
	g->id[0] = '\0';
	g->title[0] = '\0';
	g->genre[0] = '\0';
	g->sellDat[0] = '\0';
	g->rentDat[0] = '\0';
	g->lendMID[0] = '\0';
	g->lendSts[0] = '\0';
	g->lendNum[0] = '\0';
	g->keep[0] = '\0';
	g->next = NULL;
}

/*
 * �֐���			: int InputRegistGoods(GOODS *g)
 * �@�\				: �yD-1131�z�o�^���鏤�i������͂���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: GOODS *g	:���͂������i���ւ̃|�C���^
 * �߂�l			: int	:TRUE�i���iID�擾�j/FALSE�i���iID�擾���s�j
 * ���L����			: �Ȃ�
 */
int InputRegistGoods(GOODS *g)
{
	int retVal;
	char buf[INPUTREGISTGOODS_BUF_SIZE];				/* ������p�o�b�t�@ */
	char id[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];		/* ���iID�p������ */
	char f[INPUTREGISTGOODS_FORMAT_BUF_SIZE];			/* sprintf�t�H�[�}�b�g�p������ */
	
	/* �^�C�g������͂��� */
	printf("%-12s���@", GOODS_TITLE_NAME);
	buf[0] = '\0';
	while(strlen(buf) == 0) {
		GetStr(buf, GOODS_TITLE_SIZE);
	}
	strncpy_s(g->title, GOODS_TITLE_SIZE+1, buf, _TRUNCATE);
	
	/* �W����������͂��� */
	printf("%-12s���@", GOODS_GENRE_NAME);
	buf[0] = '\0';
	while(strlen(buf) == 0) {
		GetStr(buf, GOODS_GENRE_SIZE);
	}
	strncpy_s(g->genre, GOODS_GENRE_SIZE+1, buf, _TRUNCATE);
	
	/* ����������͂��� */
	printf("%s\n", GOODS_SELL_NAME);
	InputYMD(buf);
	strncpy_s(g->sellDat, GOODS_SELL_DATE_SIZE+1, buf, _TRUNCATE);
	
	/* �ݏo�E�ԋp����V�K�ݒ肷�� */
	sprintf_s(f, INPUTREGISTGOODS_FORMAT_BUF_SIZE, "%%0%dd", GOODS_RENT_DATE_SIZE);
	sprintf_s(g->rentDat, GOODS_RENT_DATE_SIZE+1, f, 0);
	
	/* �ݏo�󋵂�V�K�ݒ肷�� */
	strncpy_s(g->lendSts, GOODS_LEND_STS_SIZE+1, GOODS_LEND_NO_VAL, _TRUNCATE);
	
	/* �ݏo���ID��V�K�ݒ肷�� */
	sprintf_s(f, INPUTREGISTGOODS_FORMAT_BUF_SIZE, "%%0%dd", GOODS_LEND_MID_SIZE);
	sprintf_s(g->lendMID, MEMBER_ID_SIZE+1, f, 0);
	
	/* �ݏo�񐔂�V�K�ݒ肷�� */
	sprintf_s(f, INPUTREGISTGOODS_FORMAT_BUF_SIZE, "%%0%dd", GOODS_LEND_NUM_SIZE);
	sprintf_s(g->lendNum, GOODS_LEND_NUM_SIZE+1, f, 0);
	
	/* �ۊǏꏊ��V�K�ݒ肷�� */
	strncpy_s(g->keep, GOODS_KEEP_SIZE+1, GOODS_KEEP_WARE_VAL, _TRUNCATE);
	
	/* ���iID��V�K�ݒ肷�� */
	if(GetGoodsID(id) == FALSE) {					/* ID�̍ő�l�𒴂����ꍇ */
		printf("���iID�̎擾�Ɏ��s���܂����B\n");
		retVal = FALSE;
	} else {										/* ID���擾�ł����ꍇ */
		strncpy_s(g->id, GOODS_ID_SIZE+1, id, _TRUNCATE);
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: static int GetGoodsID(char *id)
 * �@�\				:  �yD-1131�z�V�K�̏��iID���擾����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: char *id	:�V�K�Ɏ擾�������iID
 * �߂�l			: int	:TRUE�i���iID���擾�j/FALSE�i���iID���擾�ł��Ȃ��j
 * ���L����			: "99"+���t�{3���̐����@�v13��
 */
static int GetGoodsID(char *id)
{
	int retVal = FALSE;
	GOODS *target;							/* �^�[�Q�b�g�m�[�h�p */
	char w[GETGOODSID_STR_BUF_SIZE];		/* �����񑀍�p */
	char today[GETGOODSID_DATE_BUF_SIZE];	/* �{���̓��t */
	int newID;								/* �V�KID�i����10���̐����j */
	int listID;								/* ���i��񃊃X�g����ID�i����10���̐����j */
	
	/* 10���̉��ID���쐬����iINT�^�ł�10���܂ł������Ȃ��̂Ő擪��'2'���폜����j */
	GetToday(0, 0, 0, today);					/* �����̓��t���擾 */
	strncpy_s(w, GETGOODSID_STR_BUF_SIZE, today + 1, 7);		/* 2012�N�̐擪��2���폜 */
	sprintf_s(w, GETGOODSID_STR_BUF_SIZE, "%07s%03d", w, 1);	/* ���t+"01"��ID���쐬 */
	newID = atoi(w);
	
	/* ���i��񃊃X�g���������A�V����ID���擾���� */
	target = root;
	if(target != NULL) {
		/* ���X�g���I������܂ŌJ��Ԃ� */
		while(target->next != NULL) {
			target = target->next;
			
			/* ���X�g�̏��iID�̉���10�P�^���擾����iINT�^�ł�10���܂ŗL���j */
			strncpy_s(w, GETGOODSID_STR_BUF_SIZE, target->id + 3, 10);
			listID = atoi(w);
			
			/* ID���r���� */
			if(newID == listID) {
				newID = listID + 1;
			} else if(newID > listID) {
				/* DO NOTHING */
			} else {
				break;
			}
		}
		
		/* ID�̍ő�l���`�F�b�N���� */
		if((newID % 1000) == 0) {				/* 999�𒴂��� */
			retVal = FALSE;
		} else {
			sprintf_s(id, GOODS_ID_SIZE+1, "992%010d", newID);	/* '2'��t�����ĕ�����ɕϊ� */
			retVal = TRUE;
		}
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: void DisplayRegistGoods(const GOODS *g)
 * �@�\				: �yD-1132�z�o�^���鏤�i����\������
 * ���̓p�����[�^	: GOODS *g	:���i���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayRegistGoods(const GOODS *g)
{
	char date[DISPLAYREGISTGOODS_BUF_SIZE];					/* ���t�t�H�[�}�b�g�p */
	
	printf("\n*****�V�K���i���m�F*****\n");
	printf("%-10s:%s\n", GOODS_ID_NAME, g->id);
	printf("%-10s:%s\n", GOODS_TITLE_NAME, g->title);
	printf("%-10s:%s\n", GOODS_GENRE_NAME, g->genre);
	ConvFormatDate(date, g->sellDat);
	printf("%-10s:%s\n", GOODS_SELL_NAME, date);
}

/*
 * �֐���			: int RegistGoods(const GOODS *g)
 * �@�\				: �yD-1132�z���i�������i���X�g�ɓo�^����
 * ���̓p�����[�^	: GOODS *g	:���i���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i���i����o�^�j���TRUE��Ԃ�
 * ���L����			: �Ȃ�
 */
int RegistGoods(const GOODS *g)
{
	int retVal = FALSE;
	GOODS *newone;				/* ���i���̒ǉ��m�[�h�Q�Ɨp */
	GOODS *target;				/* �^�[�Q�b�g�m�[�h�p */
	
	/* �V���ȃm�[�h��ǉ����f�[�^���i�[ */
	if((newone = (GOODS*)malloc(sizeof(GOODS))) == NULL) {		/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	
	strncpy_s(newone->id, GOODS_ID_SIZE+1, g->id, _TRUNCATE);
	strncpy_s(newone->title, GOODS_TITLE_SIZE+1, g->title, _TRUNCATE);
	strncpy_s(newone->genre, GOODS_GENRE_SIZE+1, g->genre, _TRUNCATE);
	strncpy_s(newone->sellDat, GOODS_SELL_DATE_SIZE+1, g->sellDat, _TRUNCATE);
	strncpy_s(newone->rentDat, GOODS_RENT_DATE_SIZE+1, g->rentDat, _TRUNCATE);
	strncpy_s(newone->lendMID, GOODS_LEND_MID_SIZE+1, g->lendMID, _TRUNCATE);
	strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, g->lendSts, _TRUNCATE);
	strncpy_s(newone->lendNum, GOODS_LEND_NUM_SIZE+1, g->lendNum, _TRUNCATE);
	strncpy_s(newone->keep, GOODS_KEEP_SIZE+1, g->keep, _TRUNCATE);
	
	/* ID�ŏ����ɂȂ�悤�Ƀm�[�h��ǉ����� */
	target = root;												/* �^�[�Q�b�g��擪�ɐݒ� */
	while(TRUE) {
		/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
		if(target->next != NULL) {
			/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
			if(strncmp(newone->id, target->next->id, GOODS_ID_SIZE) < 0) {
				newone->next = target->next;
				target->next = newone;
				break;
			} else {
				target = target->next;							/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
			}
		} else {
			/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
			newone->next = NULL;
			target->next = newone;
			break;
		}
	}
	return TRUE;
}

/*
 * �֐���			: void DisplayGoods(const GOODS *g)
 * �@�\				: �yD-1133�z���i����\������
 * ���̓p�����[�^	: GOODS *g	:���i���m�[�h�ւ̃A�h���X
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayGoods(const GOODS *g)
{
	char date[DISPLAYGOODS_BUF_SIZE];					/* ���t�t�H�[�}�b�g�p */
	
	printf("\n*****���i���m�F*****\n");
	printf("%-11s:%s\n", GOODS_ID_NAME, g->id);
	printf("%-11s:%s\n", GOODS_TITLE_NAME, g->title);
	printf("%-11s:%s\n", GOODS_GENRE_NAME, g->genre);
	ConvFormatDate(date, g->sellDat);
	printf("%-11s:%s\n", GOODS_SELL_NAME, date);
	ConvFormatDate(date, g->rentDat);
	printf("%-11s:%s\n", GOODS_RENT_DATE_NAME, date);
	printf("%-11s:%s\n", GOODS_LEND_MID_NAME, g->lendMID);
	printf("%-11s:%s\n", GOODS_LEND_STS_NAME, ConvLendStr(g->lendSts));
	printf("%-11s:%d\n", GOODS_LEND_NUM_NAME, atoi(g->lendNum));
	printf("%-11s:%s\n", GOODS_KEEP_NAME, ConvKeepStr(g->keep));
}

/*
 * �֐���			: int DisplayGoodsList(const int key, const int ud, const int menuNum)
 * �@�\				: �yD-1137�z���i�̈ꗗ��\������
 * ���̓p�����[�^	: const int key	:�\�[�g�L�[
 * 					: const int ud	:����/�~���i1:����/2:�~���j
 * 					: const int num	:��ʂ���̑I��ԍ��iENTER_NUM:����A�ȊO:2��ڈȍ~�j
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE(�܂��\������) / FALSE(�Ō�܂ŕ\��)
 * ���L����			: �Ȃ�
 */
int DisplayGoodsList(const int key, const int ud, const int menuNum)
{
	int retVal;
	static GOODS *target;	/* �^�[�Q�b�g�m�[�h�p */
	static int dspNo = 1;	/* �\���̍��� */
	
	char h[DISPLAYGOODSLIST_HEAD_COL_NUM][DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE];	/* �w�b�_�[���� */
	char head[DISPLAYGOODSLIST_HEAD_BUF_SIZE];	/* �w�b�_�[ */
	char f[DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM][DISPLAYGOODSLIST_HEAD_FORMAT_COL_BUF_SIZE];	/* printf�̃t�H�[�}�b�g�p */
	char date[DISPLAYGOODSLIST_DATE_BUF_SIZE];	/* ���t�t�H�[�}�b�g�p */
	int fig;									/* ���Ԃ̌��� */
	int cnt;									/* �\���J�E���^ */
	char buf[DISPLAYGOODSLIST_DSP_BUF_SIZE];	/* �\��������̒��������p */
	
	/* �ŏ��̓��͂̏ꍇ�̓��X�g��擪�ɖ߂��A�w��L�[�ŏ���/�~���Ƀ\�[�g���� */
	if(menuNum == ENTER_NUM) {
		target = root;
		dspNo = 1;
		SortGoodsList(key, ud);
	}

	/* �w�b�_�[��\������ */
	fig = GetFigure(GOODS_REG_MAX);			/* ���Ԃ̌������擾 */
	printf("\n*****���i���ꗗ*****\n");
	strncpy_s(h[GOODS_DSP_ROWNO_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_ROWNO_NAME, _TRUNCATE);
	
	/* �i�����ȉ��͕�����̒������ύX�����\�������邽�߁Astrncpy���g���Ă��Ȃ��j */
	strcpy_s(h[GOODS_DSP_ID_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_ID_NAME);
	strcpy_s(h[GOODS_DSP_TITLE_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_TITLE_NAME);
	strcpy_s(h[GOODS_DSP_GENRE_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_GENRE_NAME);
	strcpy_s(h[GOODS_DSP_SELL_DATE_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_SELL_DATE_NAME);
	strcpy_s(h[GOODS_DSP_RENT_DATE_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_RENT_DATE_NAME);
	strcpy_s(h[GOODS_DSP_LEND_STS_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_LEND_STS_NAME);
	strcpy_s(h[GOODS_DSP_KEEP_COL], DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE, GOODS_DSP_KEEP_NAME);
	sprintf_s(head, DISPLAYGOODSLIST_HEAD_BUF_SIZE, "%%-%ds %%-%ds %%-%ds %%-%ds %%-%ds %%-%ds %%-%ds %%-%ds\n",
		fig,
		GOODS_DSP_ID_NUM,
		GOODS_DSP_TITLE_NUM,
		GOODS_DSP_GENRE_NUM,
		GOODS_DSP_SELL_DATE_NUM,
		GOODS_DSP_RENT_DATE_NUM,
		GOODS_DSP_LEND_STS_NUM,
		GOODS_DSP_KEEP_NUM
	);
	printf(head, 
		h[GOODS_DSP_ROWNO_COL],
		h[GOODS_DSP_ID_COL],
		h[GOODS_DSP_TITLE_COL],
		h[GOODS_DSP_GENRE_COL],
		h[GOODS_DSP_SELL_DATE_COL],
		h[GOODS_DSP_RENT_DATE_COL],
		h[GOODS_DSP_LEND_STS_COL],
		h[GOODS_DSP_KEEP_COL]
	);
		
	/* printf�̃t�H�[�}�b�g��ݒ肷�� */
	sprintf_s(f[GOODS_DSP_ROWNO_COL],	DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%0%dd ", fig);
	sprintf_s(f[GOODS_DSP_ID_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_ID_NUM);
	sprintf_s(f[GOODS_DSP_TITLE_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_TITLE_NUM);
	sprintf_s(f[GOODS_DSP_GENRE_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_GENRE_NUM);
	sprintf_s(f[GOODS_DSP_SELL_DATE_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_SELL_DATE_NUM);
	sprintf_s(f[GOODS_DSP_RENT_DATE_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_RENT_DATE_NUM);
	sprintf_s(f[GOODS_DSP_LEND_STS_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_LEND_STS_NUM);
	sprintf_s(f[GOODS_DSP_KEEP_COL], DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM, "%%-%ds ", GOODS_DSP_KEEP_NUM);
	
	/* ���i���X�g��\������ */
	cnt = 0;
	while(target->next != NULL) {
		/* ���X�g�̓��e��\������ */
		target = target->next;
		printf(f[GOODS_DSP_ROWNO_COL], dspNo++);
		printf(f[GOODS_DSP_ID_COL], target->id);
		strncpy_s(buf, DISPLAYGOODSLIST_DSP_BUF_SIZE, target->title, _TRUNCATE);
		printf(f[GOODS_DSP_TITLE_COL], buf);
		strncpy_s(buf, DISPLAYGOODSLIST_DSP_BUF_SIZE, target->genre, _TRUNCATE);
		printf(f[GOODS_DSP_GENRE_COL], buf);
		ConvFormatDate(date, target->sellDat);
		printf(f[GOODS_DSP_SELL_DATE_COL], date);
		ConvFormatDate(date, target->rentDat);
		printf(f[GOODS_DSP_RENT_DATE_COL], date);
		printf(f[GOODS_DSP_LEND_STS_COL], ConvLendStr(target->lendSts));
		printf(f[GOODS_DSP_KEEP_COL], ConvKeepStr(target->keep));
		printf("\n");
		/* �\���y�[�W�𐧌䂷�� */
		cnt++;
		if(cnt == GOODS_MON_DSP_NUM) {
			break;
		}
	}
	
	if(target->next == NULL) {
		printf("\n�Ō�܂ŕ\�����܂����B\n");
		retVal = FALSE;
	} else {
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: static void SortGoodsList(const int key, const int ud)
 * �@�\				: �yD-1137�z���i��񃊃X�g���w��L�[�ŏ���/�~���Ƀ\�[�g����
 * ���̓p�����[�^	: const int key	:�\�[�g�L�[
 * 					: const int ud	:����/�~���i1:����/2:�~���j
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void SortGoodsList(const int key, const int ud)
{
	GOODS *sort;		/* �\�[�g��̐擪�m�[�h */
	GOODS *sTarget;		/* �\�[�g�p�^�[�Q�b�g�m�[�h */
	GOODS *rTarget;		/* ���[�g�p�^�[�Q�b�g�m�[�h */
	GOODS *newone;		/* ���i���̒ǉ��m�[�h�Q�Ɨp */
	GOODS *temp;		/* ����������p */
	int cmp;			/* strncmp�̖߂�l�p */
	
	/* �\�[�g���X�g�p�̃_�~�[�m�[�h���쐬���� */
	if((sort = (GOODS*)malloc(sizeof(GOODS))) == NULL) {			/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	sort->next = NULL;
	
	/* �^�[�Q�b�g�����[�g�̐擪�ɐݒ肷�� */
	rTarget = root;
	
	/* �\�[�g���X�g���쐬���� */
	while(rTarget->next != NULL) {
		/* ���[�g���̃m�[�h���\�[�g���ɕ��ʂ��� */
		rTarget = rTarget->next;
		if((newone = (GOODS*)malloc(sizeof(GOODS))) == NULL) {		/* �m�[�h���쐬 */
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}
		strncpy_s(newone->id, GOODS_ID_SIZE+1, rTarget->id, _TRUNCATE);
		strncpy_s(newone->title, GOODS_TITLE_SIZE+1, rTarget->title, _TRUNCATE);
		strncpy_s(newone->genre, GOODS_GENRE_SIZE+1, rTarget->genre, _TRUNCATE);
		strncpy_s(newone->sellDat, GOODS_SELL_DATE_SIZE+1, rTarget->sellDat, _TRUNCATE);
		strncpy_s(newone->rentDat, GOODS_RENT_DATE_SIZE+1, rTarget->rentDat, _TRUNCATE);
		strncpy_s(newone->lendMID, MEMBER_ID_SIZE+1, rTarget->lendMID, _TRUNCATE);
		strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, rTarget->lendSts, _TRUNCATE);
		strncpy_s(newone->lendNum, GOODS_LEND_NUM_SIZE+1, rTarget->lendNum, _TRUNCATE);
		strncpy_s(newone->keep, GOODS_KEEP_SIZE+1, rTarget->keep, _TRUNCATE);
		
		/* �m�[�h���\�[�g���X�g�ɑ}������ */
		sTarget = sort;
		while(TRUE) {
			/* ���̃m�[�h������Ȃ�΁A�\�[�g�L�[���`�F�b�N���� */
			if(sTarget->next != NULL) {
				/* �\�[�g�L�[��I������ */
				switch(key) {
				case 1:				/* 1:���iID */
					cmp = strncmp(newone->id, sTarget->next->id, GOODS_ID_SIZE);
					break;
				case 2:				/* 2:�ۊǏꏊ */
					cmp = strncmp(newone->keep, sTarget->next->keep, GOODS_KEEP_SIZE);
					break;
				case 3:				/* 3:������ */
					cmp = strncmp(newone->sellDat, sTarget->next->sellDat, GOODS_SELL_DATE_SIZE);
					break;
				case 4:				/* 4:�ݏo�E�ԋp�� */
					cmp = strncmp(newone->rentDat, sTarget->next->rentDat, GOODS_RENT_DATE_SIZE);
					break;
				default:			/* ��O */
					cmp = 0;
					break;
				}
				
				/* �ǉ��m�[�h�̃\�[�g�L�[�̏����A�~���̔���*/
				if(ud == 1) {	/* �����Ƀ\�[�g �ǉ��m�[�h�̃\�[�g�L�[�̔�r���ʂ��������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ� */
					if(cmp < 0) {
						newone->next = sTarget->next;
						sTarget->next = newone;
						break;
					} else {
						sTarget = sTarget->next;
					}
				} else {		/* �~���Ƀ\�[�g �ǉ��m�[�h�̃\�[�g�L�[�̔�r���ʂ��傫���Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ�*/
					if(cmp > 0) {
						newone->next = sTarget->next;
						sTarget->next = newone;
						break;
					} else {
						sTarget = sTarget->next;
					}
				}
			} else {
				/* �V�����m�[�h�����X�g�̖����ɒǉ����ďI������ */
				newone->next = NULL;
				sTarget->next = newone;
				break;
			}
		}
	}
	
	/* �\�[�g���X�g�ƃ��[�g���X�g�̃��[�g�����ւ��� */
	temp = root->next;
	root->next = sort->next;
	sort->next = temp;
	
	/* �\�[�g���X�g��������� */
	while(sort != NULL) {
		temp = sort;
		sort = sort->next;
		free(temp);
	}
}

/*
 * �֐���			: int InputUpdateGoods(GOODS *g)
 * �@�\				: �yD-1134�z���i���ύX���͉��
 * ���̓p�����[�^	: GOODS *g	:�ύX���鏤�i���m�[�h�ւ̃|�C���^
 * �o�̓p�����[�^	: GOODS *gBuf	:�ύX�������i���m�[�h�ւ̃|�C���^
 * �߂�l			: int	:TRUE�i���i�����擾�j/FALSE�i���iID���Ȃ��j
 * ���L����			: �����̏��i�����Q�l�ɐV���ȏ��i������͂���
 */
int InputUpdateGoods(GOODS *g, GOODS *gBuf)
{
	int retVal = TRUE;
	char buf[GOODS_TITLE_SIZE+STRING_TERMINATOR_SIZE];	/* ������p�o�b�t�@ */
	char date[INPUTUPDATEGOODS_DATE_BUF_SIZE];			/* ���t�t�H�[�}�b�g�p */
	char num[INPUTUPDATEGOODS_NUMSTR_BUF_SIZE];			/* �ݏo�񐔗p */
	
	if(g != NULL) {
		printf("�ύX���ڂ͓��͂��Ă��������B\n");
		printf("�����͍��ڂ͕ύX���܂���B\n");
		printf("%s:%s\n", GOODS_ID_NAME, g->id);

		/* ���iID���R�s�[���� */
		strncpy_s(gBuf->id, GOODS_ID_SIZE+1, g->id, _TRUNCATE);
		
		/* �^�C�g�����X�V���� */
		printf("%s:%s�@���@", GOODS_TITLE_NAME, g->title);
		GetStr(buf, GOODS_TITLE_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->title, GOODS_TITLE_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->title, GOODS_TITLE_SIZE+1, g->title, _TRUNCATE);
		}
		
		/* �W���������X�V���� */
		printf("%s:%s�@���@", GOODS_GENRE_NAME, g->genre);
		GetStr(buf, GOODS_GENRE_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->genre, GOODS_GENRE_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->genre, GOODS_GENRE_SIZE+1, g->genre, _TRUNCATE);
		}
		
		/* ���������X�V���� */
		ConvFormatDate(date, g->sellDat);
		printf("%s�i'/'������8���j:%s�@���@",GOODS_SELL_NAME, date);
		GetDateStr(buf);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->sellDat, GOODS_SELL_DATE_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->sellDat, GOODS_SELL_DATE_SIZE+1, g->sellDat, _TRUNCATE);
		}
		
		/* �ݏo�E�ԋp�����X�V���� */
		ConvFormatDate(date, g->rentDat);
		printf("%s�i'/'������8���j:%s�@���@", GOODS_RENT_DATE_NAME, date);
		GetDateStr(buf);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->rentDat, GOODS_RENT_DATE_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->rentDat, GOODS_RENT_DATE_SIZE+1, g->rentDat, _TRUNCATE);
		}
		
		/* �ݏo���ID���X�V���� */
		printf("%s:%s�@���@", GOODS_LEND_MID_NAME, g->lendMID);
		GetNumStr(buf, GOODS_LEND_MID_SIZE);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->lendMID, GOODS_LEND_MID_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->lendMID, GOODS_LEND_MID_SIZE+1, g->lendMID, _TRUNCATE);
		}
		
		/* �ݏo�󋵂��X�V���� */
		printf("%s�i1:�ݏo���A0;�ݏo�j:%s�@���@", GOODS_LEND_STS_NAME, ConvLendStr(g->lendSts));
		GetIntStr(buf, 1, 1);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->lendSts, GOODS_LEND_STS_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->lendSts, GOODS_LEND_STS_SIZE+1, g->lendSts, _TRUNCATE);
		}
		
		/* �ݏo�񐔂��X�V���� */
		printf("%s:%d�@���@", GOODS_LEND_NUM_NAME, atoi(g->lendNum));
		GetIntStr(buf, 0, GOODS_NUMBER_MAX);
		if(strlen(buf) != 0) {
			sprintf_s(num, INPUTUPDATEGOODS_NUMSTR_BUF_SIZE, "%05d", atoi(buf));			/* ����0�Ŗ��߂� */
			strncpy_s(gBuf->lendNum, GOODS_LEND_NUM_SIZE+1, num, _TRUNCATE);
		} else {
			strncpy_s(gBuf->lendNum, GOODS_LEND_NUM_SIZE+1, g->lendNum, _TRUNCATE);
		}

		/* �ۊǏꏊ���X�V���� */
		printf("%s�i1:�X���A0:�q�Ɂj:%s�@���@", GOODS_KEEP_NAME, ConvKeepStr(g->keep));
		GetIntStr(buf, 1, 1);
		if(strlen(buf) != 0) {
			strncpy_s(gBuf->keep, GOODS_KEEP_SIZE+1, buf, _TRUNCATE);
		} else {
			strncpy_s(gBuf->keep, GOODS_KEEP_SIZE+1, g->keep, _TRUNCATE);
		}
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: int DeleteGoods(const char *id)
 * �@�\				: �yD-1138�z���i���폜�ʒm���
 * ���̓p�����[�^	: const char *id	:���iID
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:1�i�폜�j/EXIT_NUM�i�폜���Ȃ��j
 * ���L����			: �Ȃ�
 */
int DeleteGoods(const char *id)
{
	int retVal = EXIT_NUM;
	GOODS *target;					/* �^�[�Q�b�g�m�[�h�p */
	GOODS *del;
	
	printf("\n*****���i���폜�m�F*****");
	if(GetYesNo("�폜���Ă���낵���ł���?") != FALSE) {
		/* ���X�g����^�[�Q�b�g�m�[�h���폜���� */
		target = root;
		while(target->next != NULL) {
			if(strncmp(target->next->id, id, GOODS_ID_SIZE) == 0) {
				del = target->next;
				target->next = target->next->next;
				free(del);
				break;
			}
			target = target->next;
		}
		WriteGoodsFile();						/* ���i��񃊃X�g�̃t�@�C�������� */
		printf("\n���i�����폜���܂����B\n");
		retVal = 1;
	}
	return retVal;
}
