/*
 * �t�@�C����	: Lend.h
 * �@�\			: �ݏo�Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  
 */

#ifndef LEND_H
#define LEND_H

/* #define�}�N�� */
/* �o�b�t�@�T�C�Y */
/* DisplayLend */
#define DISPLAYLEND_DATE_BUF_SIZE	10			/* DisplayLend ����Ɣ��f������t�̕�����i�[�p�o�b�t�@�T�C�Y */
	
/* UpdateGoodsLendSts */
#define UPDATEGOODSLENDSTS_DATE_BUF_SIZE	10	/* UpdateGoodsLendSts �ݏo���̓��t�̕�����i�[�p�o�b�t�@�T�C�Y */

/* �ݏo�F�V��/���씻�f��i����������N�Z�����N������ݒ�j */
#define LEND_OLD_YEAR			0				/* ���f�N */
#define LEND_OLD_MONTH			6				/* ���f�� */
#define LEND_OLD_DAY			0				/* ���f�� */

/* �ݏo�F�V��/����敪 */
#define LEND_NEW_VAL			"0"				/* �V��̓����l */
#define LEND_OLD_VAL			"1"				/* ����̓����l */
#define LEND_NEW_NAME			"NEW"			/* �V��̕\������ */
#define LEND_OLD_NAME			"OLD"			/* ����̕\������ */

/* �ݏo�F�����̌n */
#define LEND_NEW_PRICE			300				/* �V�엿�� */
#define LEND_OLD_PRICE			100				/* ���엿�� */

/* �ݏo�F���� */
#define LEND_MAX				10				/* �ő�ݏo���� */

/* �ݏo�F���R�[�h�T�C�Y */
#define LEND_OLD_SIZE			1				/* �V��/����敪 */

/* struct�^�O��` */
/* �ݏo��� */
typedef struct lendRent {
	char id[GOODS_ID_SIZE+1];					/* ���iID */
	char title[GOODS_TITLE_SIZE+1];				/* �^�C�g�� */
	char old[LEND_OLD_SIZE+1];					/* �V��/���� */
	char lendSts[GOODS_LEND_STS_SIZE+1];		/* �ݏo�󋵁i���g�p�j */
	struct lendRent *next;						/* ���ȎQ�ƃ|�C���^ */
}LEND;

/* �֐��v���g�^�C�v�錾 */
extern void CreateLendList(void);
extern void ClearLendBuffer(LEND *lend);
extern int DisplayLend(const GOODS *goods, LEND *lend);
extern int RegistLend(const LEND *lend);
extern void FreeLendList(void);
extern int DisplayLendList(void);
extern int UpdateGoodsLendSts(const char *mID, GOODS *goods);

#endif		/* end LEND_H */

