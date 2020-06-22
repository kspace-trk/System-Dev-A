/*
 * �t�@�C����	: lend.c
 * �@�\			: �ݏo�Ǘ����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  2012/02/14 V02L1
 */

/* �w�b�_�[�̎�荞�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "goods.h"
#include "lend.h"
#include "menu.h"

/* static�ϐ��錾 */
static LEND *root = NULL;		/* �ݏo��񃊃X�g�̐擪�m�[�h�Q�Ɨp */

/* static�֐��錾 */
static void SortLendList(void);
static char *ConvOldStr(const char *s);

/*
 * �֐���			: void CreateLendList(void)
 * �@�\				: �yD-1112�z�ݏo��񃊃X�g������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void CreateLendList(void)
{
	/* �_�~�[�m�[�h���쐬���� */
	if((root = (LEND*)malloc(sizeof(LEND))) == NULL) {
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	root->next = NULL;
}

/*
 * �֐���			: void ClearLendBuffer(LEND *lend)
 * �@�\				: �yD-1112�z�ݏo���o�b�t�@���N���A����
 * ���̓p�����[�^	: LEND *lend	:�ݏo���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: CreateLendList ���ďo��AFreeLendLsit���ďo���܂łɎg�p���邱��
 */
void ClearLendBuffer(LEND *lend)
{
	lend->id[0] = '\0';
	lend->title[0] = '\0';
	lend->old[0] = '\0';
	lend->lendSts[0] = '\0';
	lend->next = NULL;
}

/*
 * �֐���			: int DisplayLend(const GOODS *goods, LEND *lend)
 * �@�\				: �yD-1112�z���i�̑ݏo����\������
 * ���̓p�����[�^	: GOODS *goods	:���i���m�[�h�ւ̃A�h���X
 * �o�̓p�����[�^	: LEND *lend	:�ݏo���ւ̃A�h���X
 * �߂�l			: int	:�ݏo�̂Ƃ�TRUE�C�ݏo���̂Ƃ�FALSE
 * ���L����			: CreateLendList ���ďo��AFreeLendLsit���ďo���܂łɎg�p���邱��
 */
int DisplayLend(const GOODS *goods, LEND *lend)
{
	int retVal = TRUE;
	char baseDate[DISPLAYLEND_DATE_BUF_SIZE];		/* ����Ɣ��f������t */
	
	if(goods != NULL) {
		/* �V��/����𔻒f���� */
		GetToday(-LEND_OLD_YEAR, -LEND_OLD_MONTH, -LEND_OLD_DAY, baseDate);	/* �w�肵�������O�̓��t���擾 */
		if(strncmp(goods->sellDat, baseDate, 8) < 0) {						/* �������Ɣ�r */
			strncpy_s(lend->old, LEND_OLD_SIZE+1, LEND_OLD_VAL, _TRUNCATE);					/* ���� */
		} else {
			strncpy_s(lend->old, LEND_OLD_SIZE+1, LEND_NEW_VAL, _TRUNCATE);					/* �V�� */
		}
		
		/* ���i����ݏo���ɃR�s�[���� */
		strncpy_s(lend->id, GOODS_ID_SIZE+1, goods->id, _TRUNCATE);
		strncpy_s(lend->title, GOODS_TITLE_SIZE+1, goods->title, _TRUNCATE);
		strncpy_s(lend->lendSts, GOODS_LEND_STS_SIZE+1, goods->lendSts, _TRUNCATE);

		/* �ݏo����\������ */
		printf("\n*****�ݏo���i���m�F*****\n");
		printf("\n%s:%s:%s:%s\n", lend->id, lend->title, ConvOldStr(lend->old), ConvLendStr(lend->lendSts));
		if(strncmp(lend->lendSts, "1", GOODS_LEND_STS_SIZE) == 0) {			/* �ݏo�� ? */
			printf("�i���j���̏��i�͑ݏo���ł��B\n");
			retVal = FALSE;
		}
	}
	return retVal;
}

/*
 * �֐���			: int RegistLend(const LEND *lend)
 * �@�\				: �yD-1112�z�ݏo����ݏo���X�g�ɓo�^����
 * ���̓p�����[�^	: LEND *lend	:�ݏo���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�o�^�j/FALSE�i�o�^�s�j
 * ���L����			: CreateLendList ���ďo��AFreeLendLsit���ďo���܂łɎg�p���邱��
 */
int RegistLend(const LEND *lend)
{
	int retVal = FALSE;
	LEND *newone;				/* �ݏo���̒ǉ��m�[�h�Q�Ɨp */
	LEND *target;				/* �^�[�Q�b�g�m�[�h�p */
	int cnt;
	
	/* �V���ȃm�[�h��ǉ����� */
	if((newone = (LEND*)malloc(sizeof(LEND))) == NULL) {			/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	/* �ݏo�����Z�b�g���� */
	strncpy_s(newone->id, GOODS_ID_SIZE+1, lend->id, _TRUNCATE);
	strncpy_s(newone->title, GOODS_TITLE_SIZE+1, lend->title, _TRUNCATE);
	strncpy_s(newone->old, LEND_OLD_SIZE+1, lend->old, _TRUNCATE);
	strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, "", _TRUNCATE);

	/* ���X�g�̖����Ƀm�[�h��ǉ����� */
	target = root;									/* �^�[�Q�b�g��擪�ɐݒ� */
	cnt = 1;
	while(target->next != NULL) {
		target = target->next;						/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
		cnt++;
	}
	
	if(cnt > LEND_MAX) {
		printf("\n��x��%d���ȏ��݂��o�����Ƃ͂ł��܂���B\n", LEND_MAX);
		retVal = FALSE;
	} else {
		newone->next = NULL;
		target->next = newone;
		printf("\n�ݏo���X�g��%d���ڂ�ǉ����܂����B\n", cnt);
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: void FreeLendList(void)
 * �@�\				: �yD-1112�z�ݏo��񃊃X�g������������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void FreeLendList(void)
{
	LEND *temp;
	
	while(root != NULL) {
		temp = root;
		root = root->next;
		free(temp);
	}
}

/*
 * �֐���			: int DisplayLendList(void)
 * �@�\				: �yD-1113�z�ݏo���i���X�g�m�F���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�ݏo�o�^����j/FALSE�i�ݏo�o�^�Ȃ��j
 * ���L����			: �Ȃ�
 */
int DisplayLendList(void)
{
	int retVal = FALSE;
	LEND *target;				/* �^�[�Q�b�g�m�[�h�p */
	int price;					/* �������v�p */
	int cnt;					/* �J�E���^�p */
	
	target = root;						/* �^�[�Q�b�g��擪�ɐݒ� */
	price = 0;							/* �������v��0�ɏ����� */
	cnt = 0;							/* �J�E���^��0�ɏ����� */
	printf("\n*****�ݏo���i���X�g�m�F*****\n");
	if(target != NULL) {
		while(target->next != NULL) {
			target = target->next;		/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
			cnt++;
			
			/* �V�삩���삩�𔻒f���ė������v�Z���� */
			if(strncmp(target->old, LEND_NEW_VAL, LEND_OLD_SIZE) == 0) {
				price = price + LEND_NEW_PRICE;
			} else {
				price = price + LEND_OLD_PRICE;
			}
			
			printf("%02d.%s:%s:%s\n", cnt, target->id, target->title, ConvOldStr(target->old));
		}
		printf("\n�������v:%d�~\n", price);
		retVal = TRUE;
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: int UpdateGoodsLendSts(const char *mID)
 * �@�\				: �yD-1113�z���i���t�@�C���̑ݏo���ID�A�ݏo�󋵁A�ݏo�񐔂��X�V����i�}�b�`���O�j
 * ���̓p�����[�^	: const char *mID	:�ݏo���ID / GOODS *goods	:���i��񃊃X�g
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�X�V�j/FALSE�i�X�V�s�j
 * ���L����			: �Ȃ�
 */
int UpdateGoodsLendSts(const char *mID, GOODS *goods)
{
	int retVal = FALSE;
	LEND *lend;										/* �^�[�Q�b�g�m�[�h�p */
	char toDay[UPDATEGOODSLENDSTS_DATE_BUF_SIZE];	/* �ݏo���̓��t */
	int num;										/* �ݏo�� */
	
	GetToday(0, 0, 0, toDay);						/* �{���̓��t���擾 */
	SortLendList();									/* �ݏo���X�g��ID���Ƀ\�[�g */
	lend = root;									/* �^�[�Q�b�g��擪�ɐݒ� */
	
	/* ���i���t�@�C���̑ݏo�󋵂���ёݏo���ID���X�V���� */
	if((lend != NULL) && (goods != NULL)) {
		/* ���iID�Ńf�[�^�̃}�b�`���O���s�� */
		while((lend->next != NULL) && (goods->next != NULL)) {
			/* ���iID���}�b�`���O�����珤�i��񃊃X�g���X�V���� */
			if(strncmp(lend->next->id, goods->next->id, GOODS_ID_SIZE) < 0) {
				lend = lend->next;						/* �ݏo���X�g�̃m�[�h���X�V */
			} else if(strncmp(lend->next->id, goods->next->id, GOODS_ID_SIZE) > 0) {
				goods = goods->next;					/* ���i���X�g�̃m�[�h���X�V */
			} else {
				/* ���i��񃊃X�g�̑ݏo���ID���X�V���� */
				strncpy_s(goods->next->lendMID, GOODS_LEND_MID_SIZE+1, mID, _TRUNCATE);
				
				/* ���i��񃊃X�g�̑ݏo���t��{���̓��t�ɐݒ肷�� */
				strncpy_s(goods->next->rentDat, GOODS_RENT_DATE_SIZE+1, toDay, _TRUNCATE);
				
				/* ���i��񃊃X�g�̑ݏo�󋵂��u�ݏo���v�ɐݒ肷�� */
				strncpy_s(goods->next->lendSts, GOODS_LEND_STS_SIZE+1, GOODS_LEND_YES_VAL, _TRUNCATE);
				
				/* ���i��񃊃X�g�̑ݏo�񐔂��X�V���� */
				num = atoi(goods->next->lendNum);
				num++;
				if(GetFigure(num) > GOODS_LEND_NUM_SIZE) {	/* �ݏo�񐔂̌������擾 */
					printf("���iID:%s�̑ݏo�񐔂��ő�l�𒴂��܂����B", goods->next->lendMID);
					num = 0;
				}
				sprintf_s(goods->next->lendNum, GOODS_LEND_NUM_SIZE+1, "%05d", num);
				
				lend = lend->next;							/* �ݏo���X�g�̃m�[�h���X�V */
				goods = goods->next;						/* ���i���X�g�̃m�[�h���X�V */
			}
		}
		WriteGoodsFile();									/* ���i��񃊃X�g�̃t�@�C���������� */
		retVal = TRUE;
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: static void SortLendList(void)
 * �@�\				: �yD-1113�z�ݏo���X�g��ID���Ƀ\�[�g����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void SortLendList(void)
{
	LEND *sort;			/* �\�[�g��̐擪�m�[�h */
	LEND *sTarget;		/* �\�[�g�p�^�[�Q�b�g�m�[�h */
	LEND *rTarget;		/* ���[�g�p�^�[�Q�b�g�m�[�h */
	LEND *newone;		/* ���i���̒ǉ��m�[�h�Q�Ɨp */
	LEND *temp;			/* ����������p */
	int cmp;			/* strncmp�̖߂�l�p */
	
	/* �\�[�g���X�g�p�̃_�~�[�m�[�h���쐬���� */
	if((sort = (LEND*)malloc(sizeof(LEND))) == NULL) {
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
		if((newone = (LEND*)malloc(sizeof(LEND))) == NULL) {
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}
		strncpy_s(newone->id, GOODS_ID_SIZE+1, rTarget->id, _TRUNCATE);
		strncpy_s(newone->title, GOODS_TITLE_SIZE+1, rTarget->title, _TRUNCATE);
		strncpy_s(newone->old, LEND_OLD_SIZE+1, rTarget->old, _TRUNCATE);
		strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, rTarget->lendSts, _TRUNCATE);

		/* �m�[�h���\�[�g���X�g�ɑ}������ */
		sTarget = sort;
		while(TRUE) {
			/* ���̃m�[�h������Ȃ�΁AID���`�F�b�N���� */
			if(sTarget->next != NULL) {
				cmp = strncmp(newone->id, sTarget->next->id, GOODS_ID_SIZE);
				/* �ǉ��m�[�h��ID���������Ȃ�΁A�^�[�Q�b�g�̌��Ƀm�[�h��ǉ����ďI������ */
				if(cmp < 0) {
					newone->next = sTarget->next;
					sTarget->next = newone;
					break;
				} else {
					sTarget = sTarget->next;
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
 * �֐���			: static char *ConvOldStr(const char *s)
 * �@�\				: �V��/����̕\��������ɕϊ�����
 * ���̓p�����[�^	: const char *s	:0/1�̕�����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: char *dsp		:�V��/������̕�����
 * ���L����			: �Ȃ�
 */
static char *ConvOldStr(const char *s)
{
	static const char *tbl[] = {LEND_NEW_NAME, LEND_OLD_NAME};
	char *dsp;
	
	if((*s == '0') || (*s == '1')) {
		dsp = (char *)tbl[atoi(s)];
	} else {
		dsp = "�Q�Q";
	}
	return dsp;
}

