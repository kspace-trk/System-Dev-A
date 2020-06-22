/*
 * �t�@�C����	: goods.h
 * �@�\			: ���i�Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  
 */

#ifndef GOODS_H
#define GOODS_H

/* �w�b�_�[�̎�荞�� */
#include "member.h"

/* #define�}�N�� */
/* �o�b�t�@�T�C�Y */
/* WriteGoodsFile */
#define WRITEGOODSFILE_BUF_SIZE				100		/* �t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */

/* DisplayGoods */
#define DISPLAYGOODS_BUF_SIZE				16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */
	
/* InputRegistGoods */
#define INPUTREGISTGOODS_BUF_SIZE			128		/* ������p�o�b�t�@�T�C�Y */
#define INPUTREGISTGOODS_FORMAT_BUF_SIZE	8		/* sprintf�t�H�[�}�b�g�p������p�o�b�t�@�T�C�Y */

/* GetGoodsID */
#define GETGOODSID_STR_BUF_SIZE				20		/* �����񑀍�p�o�b�t�@�T�C�Y */
#define GETGOODSID_DATE_BUF_SIZE			10		/* �{���̓��t������i�[�p�o�b�t�@�T�C�Y */

/* DisplayRegistGoods */
#define DISPLAYREGISTGOODS_BUF_SIZE			16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */
	
/* InputUpdateGoods */
#define INPUTUPDATEGOODS_DATE_BUF_SIZE		16		/* ���t�t�H�[�}�b�g�p������i�[�p�o�b�t�@�T�C�Y */
#define INPUTUPDATEGOODS_NUMSTR_BUF_SIZE	8		/* �ݏo�񐔗p������i�[�p�o�b�t�@�T�C�Y */

/* DisplayGoodsList */
#define DISPLAYGOODSLIST_HEAD_COL_NUM				30	/* DisplayGoodsList �w�b�_�[���ڗ� */
#define DISPLAYGOODSLIST_HEAD_COL_BUF_SIZE			20	/* DisplayGoodsList �w�b�_�[���ڕ�����p�o�b�t�@�T�C�Y */
#define DISPLAYGOODSLIST_HEAD_BUF_SIZE				200	/* DisplayGoodsList �w�b�_�[������p�o�b�t�@�T�C�Y */
#define DISPLAYGOODSLIST_HEAD_FORMAT_COL_NUM		10	/* DisplayGoodsList printf�̃t�H�[�}�b�g������p�� */
#define DISPLAYGOODSLIST_HEAD_FORMAT_COL_BUF_SIZE	10	/* DisplayGoodsList printf�̃t�H�[�}�b�g������p�o�b�t�@�T�C�Y */
#define DISPLAYGOODSLIST_DATE_BUF_SIZE				20	/* DisplayGoodsList ���t�t�H�[�}�b�g�p������p�o�b�t�@�T�C�Y */
#define DISPLAYGOODSLIST_DSP_BUF_SIZE				40	/* DisplayGoodsList �\��������̒��������p�o�b�t�@�T�C�Y */

/* ���i�ꗗ��ʕ\�� */
#define GOODS_MON_DSP_NUM		20					/* 1��ʂ̏��i�\���� */

/* ���i�ꗗ�\���F���i���̕\������ */
#define GOODS_DSP_ID_NUM			13				/* ���iID */
#define GOODS_DSP_TITLE_NUM			14				/* �^�C�g�� */
#define GOODS_DSP_GENRE_NUM			8				/* �W������ */
#define GOODS_DSP_SELL_DATE_NUM		10				/* ������ */
#define GOODS_DSP_RENT_DATE_NUM		10				/* �ݏo�E�ԋp�� */
#define GOODS_DSP_LEND_STS_NUM		6				/* �ݏo�� */
#define GOODS_DSP_KEEP_NUM			4				/* �ۊǏꏊ */

/* ���i�ꗗ�\���F���ڕ\���� */
#define GOODS_DSP_COL_NUM				8			/* �\�����ڐ� */

/* ���i�ꗗ�\���F���ڕ\����ԍ� */
#define GOODS_DSP_ROWNO_COL			0				/* �s�ԍ� */
#define GOODS_DSP_ID_COL			1				/* ���iID */
#define GOODS_DSP_TITLE_COL			2				/* �^�C�g�� */
#define GOODS_DSP_GENRE_COL			3				/* �W������ */
#define GOODS_DSP_SELL_DATE_COL		4				/* ������ */
#define GOODS_DSP_RENT_DATE_COL		5				/* �ݏo�E�ԋp�� */
#define GOODS_DSP_LEND_STS_COL		6				/* �ݏo�� */
#define GOODS_DSP_KEEP_COL			7				/* �ۊǏꏊ */
	
/* ���i�ꗗ�\���F�\�����ږ��i�S�p��5�����ȓ��j */
#define GOODS_DSP_ROWNO_NAME		"No."			/* �s�ԍ� */
#define GOODS_DSP_ID_NAME			"���iID"		/* ���iID */
#define GOODS_DSP_TITLE_NAME		"�^�C�g��"		/* �^�C�g�� */
#define GOODS_DSP_GENRE_NAME		"�W������"		/* �W������ */
#define GOODS_DSP_SELL_DATE_NAME	"������"		/* ������ */
#define GOODS_DSP_RENT_DATE_NAME	"�ݏo�E�ԋp��"	/* �ݏo�E�ԋp�� */
#define GOODS_DSP_LEND_STS_NAME		"�ݏo��"		/* �ݏo�� */
#define GOODS_DSP_KEEP_NAME			"�ۊǏꏊ"		/* �ۊǏꏊ */

/* ���i���t�@�C�� */
#define GOODS_FILE_NAME			"goodsMST.dat"		/* ���i���t�@�C���� */
#define GOODS_REG_MAX			10000				/* ���i�ő�o�^�� */
#define GOODS_NUMBER_MAX		99999				/* �ݏo�񐔂̍ő�l */

/* ���i���t�@�C���F���ږ��i�S�p��5�����ȓ��j */
#define GOODS_ID_NAME			"���iID"			/* ���iID */
#define GOODS_TITLE_NAME		"�^�C�g��"			/* �^�C�g�� */
#define GOODS_GENRE_NAME		"�W������"			/* �W������ */
#define GOODS_SELL_NAME			"������"			/* ������ */
#define GOODS_RENT_DATE_NAME	"�ݏo�E�ԋp��"		/* �ݏo�E�ԋp�� */
#define GOODS_LEND_MID_NAME		"�ݏo���ID"		/* �ݏo���ID */
#define GOODS_LEND_STS_NAME		"�ݏo��"			/* �ݏo�� */
#define GOODS_LEND_NUM_NAME		"�ݏo��"			/* �ݏo�� */
#define GOODS_KEEP_NAME			"�ۊǏꏊ"			/* �ۊǏꏊ */

/* ���i���t�@�C���F���i���̊e�����i�\���̃����o�[�̑傫���j */
#define GOODS_ID_SIZE			13					/* ���iID */
#define GOODS_TITLE_SIZE		20					/* �^�C�g�� */
#define GOODS_GENRE_SIZE		10					/* �W������ */
#define GOODS_SELL_DATE_SIZE	8					/* ������ */
#define GOODS_RENT_DATE_SIZE	8					/* �ݏo�E�ԋp�� */
#define GOODS_LEND_MID_SIZE		12					/* �ݏo���ID */
#define GOODS_LEND_STS_SIZE		1					/* �ݏo�� */
#define GOODS_LEND_NUM_SIZE		5					/* �ݏo�� */
#define GOODS_KEEP_SIZE			1					/* �ۊǏꏊ */

/* ���i���t�@�C���F���i��񃌃R�[�h���̐擪�ʒu */
#define GOODS_ID_POS			0											/* ���iID */
#define GOODS_TITLE_POS			GOODS_ID_POS + GOODS_ID_SIZE				/* �^�C�g�� */
#define GOODS_GENRE_POS			GOODS_TITLE_POS + GOODS_TITLE_SIZE			/* �W������ */
#define GOODS_SELL_DATE_POS		GOODS_GENRE_POS + GOODS_GENRE_SIZE			/* ������ */
#define GOODS_RENT_DATE_POS		GOODS_SELL_DATE_POS + GOODS_SELL_DATE_SIZE	/* �ݏo�E�ԋp�� */
#define GOODS_LEND_MID_POS		GOODS_RENT_DATE_POS + GOODS_RENT_DATE_SIZE	/* �ݏo���ID */
#define GOODS_LEND_STS_POS		GOODS_LEND_MID_POS + GOODS_LEND_MID_SIZE	/* �ݏo�� */
#define GOODS_LEND_NUM_POS		GOODS_LEND_STS_POS + GOODS_LEND_STS_SIZE	/* �ݏo�� */
#define GOODS_KEEP_POS			GOODS_LEND_NUM_POS + GOODS_LEND_NUM_SIZE	/* �ۊǏꏊ */

/* ���i���t�@�C���F���i��񃌃R�[�h�̃T�C�Y */
#define GOODS_SIZE				GOODS_KEEP_POS + GOODS_KEEP_SIZE

/* struct�^�O��` */
/* ���i��� */
typedef struct goods {
	char id[GOODS_ID_SIZE+1];				/* ���iID */
	char title[GOODS_TITLE_SIZE+1];			/* �^�C�g�� */
	char genre[GOODS_GENRE_SIZE+1];			/* �W������ */
	char sellDat[GOODS_SELL_DATE_SIZE+1];	/* ������ */
	char rentDat[GOODS_RENT_DATE_SIZE+1];	/* �ݏo�E�ԋp�� */
	char lendMID[MEMBER_ID_SIZE+1];			/* �ݏo���ID */
	char lendSts[GOODS_LEND_STS_SIZE+1];	/* �ݏo�� */
	char lendNum[GOODS_LEND_NUM_SIZE+1];	/* �ݏo�� */
	char keep[GOODS_KEEP_SIZE+1];			/* �ۊǏꏊ */
	struct goods *next;						/* ���ȎQ�ƃ|�C���^ */
}GOODS;

/* �֐��v���g�^�C�v�錾 */
extern int ReadGoodsFile(GOODS **goods);
extern void FreeGoodsList(void);
extern int WriteGoodsFile(void);
extern int SearchGoods(const char *id, GOODS **g);
extern void ClearGoodsBuffer(GOODS *g);
extern int InputRegistGoods(GOODS *g);
extern void DisplayRegistGoods(const GOODS *g);
extern int RegistGoods(const GOODS *g);
extern void DisplayGoods(const GOODS *g);
extern int DisplayGoodsList(const int key, const int ud, const int menuNum);
extern int InputUpdateGoods(GOODS *g, GOODS *gBuf);
extern int DeleteGoods(const char *id);

#endif		/* end GOODS_H */

