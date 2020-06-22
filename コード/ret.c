/*
 * �t�@�C����	: ret.c
 * �@�\			: �ԋp�Ǘ����s��
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
#include "ret.h"
#include "menu.h"

/* static�ϐ��錾 */
static RET *root = NULL;			/* �ԋp��񃊃X�g�̐擪�m�[�h�Q�Ɨp */

/* static�֐��錾 */
static void SortRetList();
static char *ConvDelayStr(const int d);

/*
 * �֐���			: void CreateRetList(void)
 * �@�\				: �yD-1112�z�ԋp��񃊃X�g������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void CreateRetList(void)
{
	/* �_�~�[�m�[�h���쐬���� */
	if((root = (RET*)malloc(sizeof(RET))) == NULL) {
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	root->next = NULL;
}

/*
 * �֐���			: void ClearRetBuffer(RET *ret)
 * �@�\				: �yD-1112�z�ԋp���o�b�t�@���N���A����
 * ���̓p�����[�^	: RET *ret	:�ԋp���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void ClearRetBuffer(RET *ret)
{
	ret->id[0] = '\0';
	ret->title[0] = '\0';
	ret->delay = 0;
	ret->lendSts[0] = '\0';
	ret->next = NULL;
}

/*
 * �֐���			: int DisplayRet(const GOODS *goods, RET *ret)
 * �@�\				: �yD-1112�z���i�̕ԋp����\������
 * ���̓p�����[�^	: GOODS *goods	:���i���m�[�h�ւ̃A�h���X
 * �o�̓p�����[�^	: LEND *ret	:�ԋp���ւ̃A�h���X
 * �߂�l			: int	:TRUE�i���i�����擾�j/FALSE�i���iID���Ȃ��C�ԋp�ς݁j
 * ���L����			: �Ȃ�
 */
int DisplayRet(const GOODS *goods, RET *ret)
{
	int retVal = TRUE;
	char baseDate[DISPLAYRET_DATE_BUF_SIZE];			/* �����̓��t */
	
	if(goods != NULL) {
		/* ���؂𔻒f���� */
		GetToday(0, 0, -RET_DLY_DAY, baseDate);					/* ���ؓ����v�Z�̊�����擾  */
		ret->delay = DiffDate(goods->rentDat, baseDate);		/* ���ؓ����v�Z */
		
		/* ���i����ԋp���ɃR�s�[���� */
		strncpy_s(ret->id, GOODS_ID_SIZE+1, goods->id, _TRUNCATE);
		strncpy_s(ret->title, GOODS_TITLE_SIZE+1, goods->title, _TRUNCATE);
		strncpy_s(ret->lendSts, GOODS_LEND_STS_SIZE+1, goods->lendSts, _TRUNCATE);

		/* �ԋp����\������ */
		printf("\n*****�ԋp���i���m�F*****\n");
		printf("\n%s:%s:%s:%s", ret->id, ret->title, ConvDelayStr(ret->delay), ConvRetStr(ret->lendSts));
		if(ret->delay>0){
			printf(" %d�� ���ؗ��� %d�~", ret->delay,(RET_DLY_PRICE * ret->delay));
		}
		printf("\n");
		if(strncmp(ret->lendSts, "0", GOODS_LEND_STS_SIZE) == 0) {			/* �ԋp�ς� ? */
			printf("�i���j���̏��i�͕ԋp�ς݂ł��B\n");
			retVal = FALSE;
		}
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: int RegistRet(const RET *ret)
 * �@�\				: �yD-1112�z�ԋp����ԋp���X�g�ɓo�^����
 * ���̓p�����[�^	: RET *ret	:�ԋp���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�o�^�j/FALSE�i�o�^�s�j
 * ���L����			: �Ȃ�
 */
int RegistRet(const RET *ret)
{
	int retVal = FALSE;
	RET *newone;		/* �ԋp���̒ǉ��m�[�h�Q�Ɨp */
	RET *target;		/* �^�[�Q�b�g�m�[�h�p */
	int cnt;
	
	/* �V���ȃm�[�h��ǉ����� */
	if((newone = (RET*)malloc(sizeof(RET))) == NULL) {		/* �m�[�h���쐬 */
		printf("���I�������̎擾�Ɏ��s���܂����B\n");
		exit(EXIT_FAILURE);
	}
	
	/* �ԋp�����Z�b�g���� */
	strncpy_s(newone->id, GOODS_ID_SIZE+1, ret->id, _TRUNCATE);
	strncpy_s(newone->title, GOODS_TITLE_SIZE+1, ret->title, _TRUNCATE);
	strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, "", _TRUNCATE);
	newone->delay = ret->delay;

	/* ���X�g�̖����Ƀm�[�h��ǉ����� */
	target = root;											/* �^�[�Q�b�g��擪�ɐݒ� */
	cnt = 1;												/* �J�E���^��1�ɏ����� */
	while(target->next != NULL) {
		target = target->next;								/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
		cnt++;
	}
	
	if(cnt > RET_MAX) {
		printf("\n��x��%d���ȏ��ԋp���邱�Ƃ͂ł��܂���B\n", RET_MAX);
		retVal = FALSE;
	} else {
		newone->next = NULL;
		target->next = newone;
		printf("\n�ԋp���X�g��%d���ڂ�ǉ����܂����B\n", cnt);
		retVal = TRUE;
	}
	return retVal;
}

/*
 * �֐���			: void FreeRetList(void)
 * �@�\				: �yD-1112�z�ԋp��񃊃X�g������������������
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void FreeRetList(void)
{
	RET *temp;
	
	while(root != NULL) {
		temp = root;
		root = root->next;
		free(temp);
	}
}

/*
 * �֐���			: int DisplayRetList(void)
 * �@�\				: �yD-1114�z�ԋp���i���X�g�m�F���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�o�^�j/FALSE�i�o�^�s�j
 * ���L����			: �Ȃ�
 */
int DisplayRetList(void)
{
	int retVal = FALSE;
	RET *target;				/* �^�[�Q�b�g�m�[�h�p */
	int price;
	int cnt;
	
	target = root;									/* �^�[�Q�b�g��擪�ɐݒ� */
	price = 0;										/* ���؊z��0�ɏ����� */
	cnt = 0;										/* �J�E���^��0�ɏ����� */
	printf("\n*****�ԋp���i���X�g�m�F*****\n");
	if(target != NULL) {
		while(target->next != NULL) {
			target = target->next;					/* �^�[�Q�b�g���X�V���Ď��̃m�[�h�� */
			cnt++;
			
			/* ���؂����邩�Ȃ����𔻒f���ė������v�Z���� */
			if(target->delay > 0) {
				price = price + (RET_DLY_PRICE * target->delay);
			}
			
			printf("%02d.%s:%-20s:%s", cnt, target->id, target->title, ConvDelayStr(target->delay));
			if(target->delay>0){
				printf(" %3d�� ���ؗ��� %5d�~", target->delay, (RET_DLY_PRICE * target->delay));
			}
			printf("\n");
		}
		printf("\n���ؗ������v:%d�~\n", price);
		retVal = TRUE;
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: int UpdateGoodsRetSts(void)
 * �@�\				: �yD-1114�z���i���t�@�C���̑ݏo�E�ԋp���A�ݏo�󋵂��X�V����i�}�b�`���O�j
 * ���̓p�����[�^	: GOODS *goods	:���i��񃊃X�g
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE�i�X�V�j/FALSE�i�X�V�s�j
 * ���L����			: �Ȃ�
 */
int UpdateGoodsRetSts(GOODS *goods)
{
	int retVal = FALSE;
	RET *ret;										/* �^�[�Q�b�g�m�[�h�p */
	char today[UPDATEGOODSRETSTS_DATE_BUF_SIZE];	/* �{���̓��t�i�[�p */
	
	GetToday(0, 0, 0, today);						/* �{���̓��t���擾 */
	SortRetList();									/* �ԋp���X�g��ID���Ƀ\�[�g */
	ret = root;										/* �^�[�Q�b�g��擪�ɐݒ� */
	
	/* ���i���t�@�C���̑ݏo�󋵂��X�V���� */
	if((ret != NULL) && (goods != NULL)) {
		/* ���iID�Ńf�[�^�̃}�b�`���O���s�� */
		while((ret->next != NULL) && (goods->next != NULL)) {
			/* ���iID���}�b�`���O�����珤�i��񃊃X�g���X�V���� */
			if(strncmp(ret->next->id, goods->next->id, GOODS_ID_SIZE) < 0) {
				ret = ret->next;					/* �ԋp���X�g�̃m�[�h���X�V */
			} else if(strncmp(ret->next->id, goods->next->id, GOODS_ID_SIZE) > 0) {
				goods = goods->next;				/* ���i���X�g�̃m�[�h���X�V */
			} else {
				/* ���i��񃊃X�g�̑ݏo�󋵂��u�ݏo�v�ɐݒ肷�� */
				strncpy_s(goods->next->lendSts, GOODS_LEND_STS_SIZE+1, GOODS_LEND_NO_VAL, _TRUNCATE);
				/* ���i��񃊃X�g�̑ݏo�E�ԋp����{���̓��t�ɐݒ肷�� */
				strncpy_s(goods->next->rentDat, GOODS_RENT_DATE_SIZE+1, today, _TRUNCATE);
				
				ret = ret->next;					/* �ԋp���X�g�̃m�[�h���X�V */
				goods = goods->next;				/* ���i���X�g�̃m�[�h���X�V */
			}
		}
		WriteGoodsFile();							/* ���i��񃊃X�g�̃t�@�C���������� */
		retVal = TRUE;
	} else {
		retVal = FALSE;
	}
	return retVal;
}

/*
 * �֐���			: static void SortRetList(void)
 * �@�\				: �yD-1114�z�ԋp���X�g��ID���Ƀ\�[�g����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
static void SortRetList(void)
{
	RET *sort;			/* �\�[�g��̐擪�m�[�h */
	RET *sTarget;		/* �\�[�g�p�^�[�Q�b�g�m�[�h */
	RET *rTarget;		/* ���[�g�p�^�[�Q�b�g�m�[�h */
	RET *newone;		/* ���i���̒ǉ��m�[�h�Q�Ɨp */
	RET *temp;			/* ����������p */
	int cmp;			/* strncmp�̖߂�l�p */
	
	/* �\�[�g���X�g�p�̃_�~�[�m�[�h���쐬���� */
	if((sort = (RET*)malloc(sizeof(RET))) == NULL) {
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
		if((newone = (RET*)malloc(sizeof(RET))) == NULL) {
			printf("���I�������̎擾�Ɏ��s���܂����B\n");
			exit(EXIT_FAILURE);
		}
		strncpy_s(newone->id, GOODS_ID_SIZE+1, rTarget->id, _TRUNCATE);
		strncpy_s(newone->title, GOODS_TITLE_SIZE+1, rTarget->title, _TRUNCATE);
		strncpy_s(newone->lendSts, GOODS_LEND_STS_SIZE+1, rTarget->lendSts, _TRUNCATE);
		newone->delay = rTarget->delay;

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
 * �֐���			: static char *ConvDelayStr(const int d)
 * �@�\				: ���؂̕\��������ɕϊ�����
 * ���̓p�����[�^	: const int d: ���ؓ���
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: char *dsp		:���؏�Ԃ̕���
 * ���L����			: �Ȃ�
 */
static char *ConvDelayStr(const int d)
{
	char *dsp;
	
	if(d > 0) {
		dsp = RET_DLY_YES_NAME;
	} else {
		dsp = RET_DLY_NO_NAME;
	}
	return dsp;
}

