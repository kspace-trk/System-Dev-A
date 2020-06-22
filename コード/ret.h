/*
 * �t�@�C����	: ret.h
 * �@�\			: �ԋp�����Ǘ�����
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  
 */

#ifndef RET_H
#define RET_H

/* #define�}�N�� */
/* �o�b�t�@�T�C�Y */
/* DisplayRet */
#define DISPLAYRET_DATE_BUF_SIZE	10			/* DisplayRet �����̓��t�̕�����i�[�p�o�b�t�@�T�C�Y */
	
/* UpdateGoodsRetSts */
#define UPDATEGOODSRETSTS_DATE_BUF_SIZE	10		/* UpdateGoodsRetSts �{���̓��t�̕�����i�[�p�o�b�t�@�T�C�Y */

/* �ԋp�F���؂���/�Ȃ����f��i�ݏo�E�ԋp������N�Z�����N������ݒ�j */
#define RET_DLY_YEAR			0				/* ���f�N */
#define RET_DLY_MONTH			0				/* ���f�� */
#define RET_DLY_DAY				7				/* ���f�� */

/* �ԋp�F���؋敪 */
#define RET_DLY_NO_VAL			"0"				/* ���؂Ȃ��̓����l */
#define RET_DLY_YES_VAL			"1"				/* ���؂���̓����l */
#define RET_DLY_NO_NAME			"���؂Ȃ�"		/* ���؂Ȃ����� */
#define RET_DLY_YES_NAME		"���؂���"		/* ���؂��蕶�� */

/* �ԋp�F�����̌n */
#define RET_DLY_PRICE			100				/* ���ؗ��� */

/* �ԋp�F���� */
#define RET_MAX					10				/* �ő�ԋp���� */

/* �ԋp�F���R�[�h�T�C�Y */
#define RET_DELAY_SIZE			1				/* ���؂���/�Ȃ� */

/* struct�^�O��` */
/* �ԋp��� */
typedef struct retRent {
	char id[GOODS_ID_SIZE+1];					/* ���iID */
	char title[GOODS_TITLE_SIZE+1];				/* �^�C�g�� */
	int delay;									/* ���ؓ��� */
	char lendSts[GOODS_LEND_STS_SIZE+1];		/* �ݏo�� */
	struct retRent *next;						/* ���ȎQ�ƃ|�C���^ */
}RET;

/* �֐��v���g�^�C�v�錾 */
extern void CreateRetList(void);
extern void ClearRetBuffer(RET *ret);
extern int DisplayRet(const GOODS *g, RET *ret);
extern int RegistRet(const RET *ret);
extern void FreeRetList(void);
extern int DisplayRetList(void);
extern int UpdateGoodsRetSts(GOODS *goods);

#endif		/* end RET_H */

