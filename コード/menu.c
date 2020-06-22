/*
 * �t�@�C����	: menu.c
 * �@�\			: ���j���[�\�����s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  2012/02/14 V02L1
 */

/* �w�b�_�[�̎�荞�� */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "common.h"
#include "menu.h"
#include "member.h"
#include "goods.h"
#include "lend.h"
#include "ret.h"

/* �ϐ��錾 */
/* �yD-1100�z�X�^�b�t���C�����j���[ */
MENU mainMenu = {
	"\n*****�X�^�b�t���C�����j���[*****",
	1, "�����^�����j���[",
	2, "������Ǘ����j���[",
	3, "���i���Ǘ����j���[",
	0, "�I��"
};

/* �yD-1110�z�����^�����j���[ */
MENU rentalMenu = {
	"\n*****�����^�����j���[*****",
	1, "�ݏo",
	2, "�ԋp",
	0, "�X�^�b�t���C�����j���[�ɖ߂�"
};

/* �yD-1111�z���iID���͉�ʁi�����^���j */
TITLE goodsIDGetRMenu = {
	"���iID�i13���j����͂��Ă��������B�i�I��:1 / �߂�:0�j���@"
};

/* �yD-1111�z���iID���͉�ʁi���i���t�@�C���j */
TITLE goodsIDGetSMenu = {
	"���iID�i13���j����͂��Ă��������B�i�߂�:0�j���@"
};

/* �yD-1112�z���i���m�F��ʁi�ݏo�j */
MENU rentalRentSMenu = {
	"",
	1, "�ݏo���X�g�ɓo�^",
	2, "�ē���",
	0, "�����^�����j���[�ɖ߂�"
};

/* �yD-1112�z���i���m�F��ʁi�ԋp�j */
MENU rentalRetSMenu = {
	"",
	1, "�ԋp���X�g�ɓo�^",
	2, "�ē���",
	0, "�����^�����j���[�ɖ߂�"
};

/* �yD-1120�z������Ǘ����j���[ */
MENU memberManageMenu = {
	"\n*****������Ǘ����j���[*****",
	1, "�o�^",
	2, "�ύX/�m�F/�폜",
	0, "�X�^�b�t���C�����j���[�ɖ߂�"
};

/* �yD-1121�z���ID���͉�ʁi���i���t�@�C���j */
TITLE memberIDGetSMenu = {
	"���ID�i12���j����͂��Ă��������B�i�߂�:0�j���@"
};

/* �yD-1122�z�V�K��������͉�� */
MENU memberRegistInputSMenu = {
	"\n*****�V�K���������*****",
	1, "������",
	0, "������Ǘ����j���[�ɖ߂�"
};

/* �yD-1123�z�V�K������m�F��� */
MENU memberRegistCheckSMenu = {
	"",
	1, "�o�^",
	0, "�V�K��������͉�ʂɖ߂�"
};

/* �yD-1124�z������m�F��� */
MENU memberUpdateSMenu = {
	"",
	1, "�ύX",
	2, "�폜",
	0, "������Ǘ����j���[�ɖ߂�"
};

/* �yD-1125�z������ύX���͉�� */
MENU memberUpdateInputSMenu = {
	"\n*****������ύX����*****",
	1, "���ύX",
	0, "������Ǘ����j���[�ɖ߂�"
};

/* �yD-1126�z������ύX�m�F��� */
MENU memberUpdateCheckSMenu = {
	"",
	1, "�ύX",
	0, "������ύX���͉�ʂɖ߂�"
};

/* �yD-1130�z���i���Ǘ����j���[ */
MENU goodsManageMenu = {
	"\n*****���i���Ǘ����j���[*****",
	1, "�o�^",
	2, "�ύX/�m�F/�폜",
	3, "�ꗗ�\��",
	0, "�X�^�b�t���C�����j���[�ɖ߂�"
};

/* �yD-1131�z�V�K���i�����͉�� */
MENU goodsRegistInputSMenu = {
	"\n*****�V�K���i������*****",
	1, "������",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* �yD-1132�z�V�K���i���m�F��� */
MENU goodsRegistCheckSMenu = {
	"",
	1, "�o�^",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* �yD-1133�z���i���m�F��� */
MENU goodsUpdateSMenu = {
	"",
	1, "�ύX",
	2, "�폜",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* �yD-1134�z���i���ύX���͉�� */
MENU goodsUpdateInputSMenu = {
	"\n*****���i���ύX����*****",
	1, "���ύX",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* �yD-1135�z���i���ύX�m�F��� */
MENU goodsUpdateCheckSMenu = {
	"",
	1, "�ύX",
	0, "���i���ύX���͉�ʂɖ߂�"
};

/* �yD-1137�z���i�ꗗ�\�����ڑI����� */
MENU goodsSortKeySMenu = {
	"\n*****���i�ꗗ�\�����ڑI��*****\n"
	"�ǂ̍��ڂŕ��ёւ��ĕ\�����܂����H",
	1, "���iID",
	2, "�ۊǏꏊ",
	3, "������",
	4, "�ݏo�E�ԋp��",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* �yD-1138�z���i�ꗗ�\�����I����� */
MENU goodsSortUdSMenu = {
	"\n*****���i�ꗗ�\�����I��*****",
	1, "����",
	2, "�~��",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* �yD-1139�z���i�ꗗ�\����� */
MENU goodsListCheckSMenu = {
	"",
	1, "���y�[�W��\��",
	0, "���i���Ǘ����j���[�ɖ߂�"
};

/* static�֐��錾 */
static int RentalMenu(void);
static int GoodsIDGetRMenu(const int size, char *id, GOODS **g);
static int RentalLendSMenu(void);
static int RentalRetSMenu(void);
static int MemberManageMenu(void);
static int MemberRegistInputSMenu(void);
static int MemberRegistCheckSMenu(const MEMBER *m);
static int MemberIDGetSMenu(const int size, char *id, MEMBER **m);
static int MemberUpdateSMenu(void);
static int MemberUpdateInputSMenu(MEMBER *m);
static int MemberUpdateCheckSMenu(MEMBER *m, MEMBER *mBuf);
static int GoodsManageMenu(void);
static int GoodsRegistInputSMenu(void);
static int GoodsRegistCheckSMenu(const GOODS *goods);
static int GoodsIDGetSMenu(const int size, char *id, GOODS **g);
static int GoodsUpdateSMenu(void);
static int GoodsUpdateInputSMenu(GOODS *goods);
static int GoodsUpdateCheckSMenu(GOODS *goods, GOODS *gBuf);
static int GoodsSortKeySMenu(void);
static int GoodsSortUdSMenu(const int key);
static int GoodsListCheckSMenu(const int key, const int ud);

/*
 * �֐���			: int MainMenu(void)
 * �@�\				: �yD-1100�z�X�^�b�t���C�����j���[
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ�(�K��EXIT_NUM��Ԃ�)
 * ���L����			: �Ȃ�
 */
int MainMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	
	while(num != EXIT_NUM) {
		num = GetMenuNum(&mainMenu);
		retVal = num;
		switch(num) {
		case 1:	
			RentalMenu();					/* �yD-1110�z�����^�����j���[ */
			break;
		case 2:
			MemberManageMenu();				/* �yD-1120�z������Ǘ����j���[ */
			break;
		case 3:
			GoodsManageMenu();				/* �yD-1130�z���i���Ǘ����j���[ */
			break;
		case EXIT_NUM:
			if(ExitProgram() == FALSE) {	/* �v���O�����I���m�F */
				num = ENTER_NUM;
			}
			break;
		default:							/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: int ExitProgram(void)
 * �@�\				: �v���O�����̏I���m�F
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I������:TRUE / �I�����Ȃ�:FALSE
 * ���L����			: �Ȃ�
 */
int ExitProgram(void)
{
	int retVal = FALSE;		/* �߂�l */
	
	retVal = GetYesNo("�v���O�������I�����Ă���낵���ł���?");
	return retVal;
}

/*
 * �֐���			: static int RentalMenu(void)
 * �@�\				: �yD-1110�z�����^�����j���[
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ�
 * ���L����			: �Ȃ�
 */
static int RentalMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	
	while(num != EXIT_NUM) {
		num = GetMenuNum(&rentalMenu);
		retVal = num;
		switch(num) {
		case 1:
			RentalLendSMenu();	/* �yD-1112�z���i���m�F��ʁi�ݏo�j */
			break;
		case 2:
			RentalRetSMenu();	/* �yD-1112�z���i���m�F��ʁi�ԋp�j */
			break;
		case EXIT_NUM:			/* �X�^�b�t���C�����j���[�� */
			break;
		default:				/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsIDGetRMenu(const int size, char *id, GOODS **g)
 * �@�\				: �yD-1111�z���iID���͉�ʁi�����^���j
 * ���̓p�����[�^	: const int size	:����
 * �o�̓p�����[�^	: char *id	:���iID
 *					: GOODS **g	:���i���m�[�h�ւ̃|�C���^�ւ̃A�h���X
 * �߂�l			: int	:�I��ԍ��i'1'�����:REGIST_NUM / '0'�܂���NULL�����:EXIT_NUM / ����ȊO�����:ENTER_NUM�j
 * ���L����			: ������ID����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
static int GoodsIDGetRMenu(const int size, char *id, GOODS **g)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	GOODS *search;
	
	while(TRUE) {
		DisplayTitle(&goodsIDGetRMenu);						/* �^�C�g����\�� */
		GetNumStr(id, size);								/* ID�𕶎���Ƃ��Ď擾 */
		if((id[0] == '1') && (id[1] == '\0')) {				/* ID���͂� "1"�̏ꍇ */
			retVal = REGIST_NUM;							/* �A���ݏo/�ԋp�����̏I�� */
			break;
		} else if((id[0] == '0') && (id[1] == '\0')) {		/* ID���͂�"0"�̏ꍇ */
			retVal = EXIT_NUM;								/* �O�ɖ߂� */
			break;
		} else if(id[0] == '\0') {							/* ID���͂�NULL�̏ꍇ */
			retVal = EXIT_NUM;
			break;
		} else {											/* ID���͂�����ꍇ */
			/* ���i��񃊃X�g���������� */
			if(SearchGoods(id, &search) == FALSE) {
				printf("�Y�����鏤�iID������܂���B\n");
			} else {
				*g = search;
				break;
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: static int RentalLendSMenu(void)
 * �@�\				: �yD-1112�z���i���m�F��ʁi�ݏo�j
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:ENTER_NUM
 * ���L����			: �Ȃ�
 */
static int RentalLendSMenu(void)
{
	int retVal = ENTER_NUM;								/* �߂�l */
	int num = ENTER_NUM;								/* ���͔ԍ� */
	char gID[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];		/* ���iID */
	GOODS *goodslist = NULL;							/* ���i��񃊃X�g�ւ̃|�C���^ */
	GOODS *goods = NULL;								/* ���i���m�[�h�ւ̃|�C���^ */
	MEMBER *member = NULL;								/* ������m�[�h�ւ̃|�C���^ */
	LEND lendBuf;										/* �ݏo��� */
	char mID[MEMBER_ID_SIZE+STRING_TERMINATOR_SIZE];	/* ���ID */
	
	/* ���i��񂨂�щ���������X�g�\���ɓǂݍ��� */
	ReadGoodsFile(&goodslist);
	ReadMemberFile(&member);
	
	/* �ݏo��񃊃X�g���쐬���A�_�~�[�m�[�h�̃A�h���X���擾���� */
	CreateLendList();
	
	/* ���iID����͂��đݏo�������s�� */
	ClearLendBuffer(&lendBuf);									/* �ݏo���o�b�t�@���N���A */
	while(num != EXIT_NUM) {
		/* �L���ȏ��iID�����͂��ꂽ��ݏo���i����\������ */
		switch(GoodsIDGetRMenu(GOODS_ID_SIZE, gID, &goods)) {	/* �yD-1111�z���iID���͉�� */
		case EXIT_NUM:											/* �߂�(0) */
			num = EXIT_NUM;
			break;
		case REGIST_NUM:										/* ���͏I��(1) */
			if(strlen(lendBuf.id) != 0) {						/* �ݏo�o�^��1��ȏ�s���Ă��� ? */
				DisplayLendList();								/* �yD-1113�z�ݏo���i���X�g�m�F��� */
				if(MemberIDGetSMenu(MEMBER_ID_SIZE, mID, &member) != EXIT_NUM) {	/* �yD-1121�z���ID���͉�� */
					UpdateGoodsLendSts(mID, goodslist);			/* ���i���t�@�C���̑ݏo�󋵂��X�V */
					printf("\n�ݏo�������������܂����B\n");
				}
				num = EXIT_NUM;
			} else {
				printf("���iID���܂���x�����͂���Ă��܂���B\n");
			}
			break;
		default:												/* �L���ȏ��iID */
			/* ���i�̑ݏo����\������ */
			if(DisplayLend(goods, &lendBuf)) {						/* lendBuf�ɒl������ */
				num = GetMenuNum(&rentalRentSMenu);
			} else {
				num = 2;
			}
			switch(num) {
			case 1:												/* ���X�g�o�^ */
				RegistLend(&lendBuf);							/* �ݏo���X�g�Ƀm�[�h��o�^ */
				break;
			case 2:												/* �ē��� */
				break;
			case EXIT_NUM:
				break;
			default:	/* NOT REACHED */
				break;
			}
			break;
		}
	}
	
	/* ���X�g������������������ */
	FreeGoodsList();
	FreeMemberList();
	FreeLendList();
	
	return retVal;
}

/*
 * �֐���			: static int RentalRetSMenu(void)
 * �@�\				: �yD-1112�z���i���m�F��ʁi�ԋp�j
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:ENTER_NUM
 * ���L����			: �Ȃ�
 */
static int RentalRetSMenu(void)
{
	int retVal = ENTER_NUM;							/* �߂�l */
	int num = ENTER_NUM;							/* ���͔ԍ� */
	char gID[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];	/* ���iID */
	GOODS *goodslist = NULL;						/* ���i��񃊃X�g�ւ̃|�C���^ */
	GOODS *goods = NULL;							/* ���i���m�[�h�ւ̃|�C���^ */
	RET retBuf;										/* �ԋp��� */
	
	/* ���i�������X�g�\���ɓǂݍ��� */
	ReadGoodsFile(&goodslist);
	
	/* �ԋp��񃊃X�g�������� */
	CreateRetList();
	
	/* ���iID����͂��ĕԋp�������s�� */
	ClearRetBuffer(&retBuf);									/* �ԋp���o�b�t�@���N���A */
	while(num != EXIT_NUM) {
		/* �L���ȏ��iID�����͂��ꂽ��ԋp���i����\������ */
		switch(GoodsIDGetRMenu(GOODS_ID_SIZE, gID, &goods)) {	/* �yD-1111�z���iID���͉�� */
		case EXIT_NUM:											/* �߂�(0) */
			num = EXIT_NUM;
			break;
		case REGIST_NUM:										/* ���͏I��(1) */
			if(strlen(retBuf.id) != 0) {						/* �ԋp�o�^��1��ȏ�s���Ă��� ? */
				DisplayRetList();								/* �yD-1114�z�ԋp���i���X�g�m�F��� */
				if(GetYesNo("�ԋp���܂���?") != FALSE) {		/* �ԋp�m�F  */
					UpdateGoodsRetSts(goodslist);				/* ���i���t�@�C���̑ݏo�󋵂��X�V */
					printf("\n�ԋp�������������܂����B\n");
				}
				num = EXIT_NUM;
			} else {
				printf("���iID���܂���x�����͂���Ă��܂���B\n");
			}
			break;
		default:												/* �L���ȏ��iID */
			/* ���i�̑ݏo����\������ */
			if(DisplayRet(goods, &retBuf)) {
				num = GetMenuNum(&rentalRetSMenu);
			} else {
				num = 2;
			}
			switch(num) {
			case 1:												/* ���X�g�o�^ */
				RegistRet(&retBuf);								/* �ԋp���X�g�Ƀm�[�h�o�^ */
				break;
			case 2:												/* �ē��� */
				break;
			case EXIT_NUM:
				break;
			default:											/* NOT REACHED */
				break;
			}
			break;
		}
	}
	
	/* ���X�g������������������ */
	FreeGoodsList();
	FreeRetList();
	
	return retVal;
}

/*
 * �֐���			: static int MemberManageMenu(void)
 * �@�\				: �yD-1120�z������Ǘ����j���[
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ�
 * ���L����			: �Ȃ�
 */
static int MemberManageMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	MEMBER *member = NULL;		/* ���i���m�[�h�ւ̃|�C���^ */

	ReadMemberFile(&member);				/* ���i���t�@�C���̓Ǎ��� */
	while (num != EXIT_NUM) {
		num = GetMenuNum(&memberManageMenu);
		retVal = num;
		switch (num) {
		case 1:
			MemberRegistInputSMenu();	/* �yD-1131�z�V�K���i�����͉�� */
			break;
		case 2:
			MemberUpdateSMenu();			/* �yD-1133�z���i���m�F��� */
			break;
		case EXIT_NUM:
			break;
		default:						/* NOT REACHED */
			break;
		}
	}
	FreeMemberList();					/* ���i��񃊃X�g�̉�� */
	return retVal;
}

/*
 * �֐���			: static int MemberRegistInputSMenu(void)
 * �@�\				: �yD-1122�z�V�K��������͉��
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�o�^:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int MemberRegistInputSMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	MEMBER *member = NULL;		/* ���i���m�[�h�ւ̃|�C���^ */
	MEMBER mBuf;					/* ���i��� */

	/* ���j���[��\������ */
	while (num != EXIT_NUM) {
		num = GetMenuNum(&memberRegistInputSMenu);
		retVal = num;
		switch (num) {
		case 1:											/* ������ */
			ClearMemberBuffer(&mBuf);					/* �o�b�t�@���N���A */
			if (InputRegistMember(&mBuf) != FALSE) {		/* �o�^���鏤�i������� */
				num = MemberRegistCheckSMenu(&mBuf);		/* �yD-1132�z�V�K���i���m�F��� */
			}
			break;
		case EXIT_NUM:									/* �߂� */
			break;
		default:										/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int MemberRegistCheckSMenu(const MEMBER *m)
 * �@�\				: �yD-1123�z�V�K������m�F���
 * ���̓p�����[�^	: const MEMBER *m:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�o�^:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int MemberRegistCheckSMenu(const MEMBER *m)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
			/* ���i���t�@�C���̓Ǎ��� */
	DisplayRegistMember(m);					/* �o�^���鏤�i����\�� */
	while (num != EXIT_NUM) {
		num = GetMenuNum(&memberRegistCheckSMenu);
		retVal = num;
		switch (num) {
		case 1:									/* �o�^ */
			RegistMember(m);					/* ���i�������X�g�ɓo�^ */
			WriteMemberFile();					/* ���i��񃊃X�g�̃t�@�C�������� */
			printf("\n�V�K�������o�^���܂����B\n");
			num = EXIT_NUM;
			break;
		case EXIT_NUM:							/* �߂� */
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int MemberIDGetSMenu(const int size, char *id, MEMBER **m)
 * �@�\				: �yD-1121�z���ID���͉��
 * ���̓p�����[�^	: const int size	:����
 * �o�̓p�����[�^	: char *id	:���ID MEMBER **m:������m�[�h�ւ̃|�C���^�ւ̃A�h���X
 * �߂�l			: int	:�I��ԍ��i'0'�܂���NULL�����:EXIT_NUM / ����ȊO�����:ENTER_NUM�j
 * ���L����			: ������ID����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
static int MemberIDGetSMenu(const int size, char *id, MEMBER **m)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	MEMBER *search;
	
	while(TRUE) {
		DisplayTitle(&memberIDGetSMenu);				/* �^�C�g����\�� */
		GetNumStr(id, size);							/* ID�𕶎���Ƃ��Ď擾 */
		if((id[0] == '0') && (id[1] == '\0')) {			/* ID���͂�'0'�̏ꍇ */
			retVal = EXIT_NUM;
			break;
		} else if(id[0] == '\0') {						/* ID���͂�NULL�̏ꍇ */
			retVal = EXIT_NUM;
			break;
		} else {										/* ID���͂�����ꍇ */
			/* �����񃊃X�g���������� */
			if(SearchMember(id, &search) == FALSE) {
				printf("�Y��������ID������܂���B\n");
			} else {
				*m = search;
				break;
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: static int MemberUpdateSMenu(void)
 * �@�\				: �yD-1124�z������m�F���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�ύX�E�폜:1 / �߂�E�ύX���Ȃ��E�폜���Ȃ�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int MemberUpdateSMenu(void)
{
	int retVal = ENTER_NUM;							/* �߂�l */
	int num = ENTER_NUM;							/* ���͔ԍ� */
	char id[MEMBER_ID_SIZE + STRING_TERMINATOR_SIZE];	/* ���iID */
	MEMBER *m = NULL;							/* ���i���m�[�h�ւ̃|�C���^ */

	while (num != EXIT_NUM) {
		num = MemberIDGetSMenu(MEMBER_ID_SIZE, id, &m);	/* �yD-1111�z���iID���͉�� */
		retVal = num;
		if (num != EXIT_NUM) {		/* �L���ȏ��iID�����͂��ꂽ��A���i���ƃ��j���[��\�� */
			DisplayMember(m);							/* ���i����\�� */
			num = GetMenuNum(&memberUpdateSMenu);
			retVal = num;
			switch (num) {
			case 1:											/* �ύX */
				num = MemberUpdateInputSMenu(m);			/* �yD-1134�z���i���ύX��� */
				break;
			case 2:											/* �폜 */
				num = DeleteMember(id);						/* ���i�����폜 */
				break;
			case EXIT_NUM:									/* �߂� */
				break;
			default:										/* NOT REACHED */
				break;
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: static int MemberUpdateInputSMenu(MEMBER* m)
 * �@�\				: �yD-1125�z������ύX���͉��
 * ���̓p�����[�^	: MEMBER *m	:������ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�ύX:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int MemberUpdateInputSMenu(MEMBER* m)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	MEMBER mBuf;					/* ���i��� */

	while (num != EXIT_NUM) {
		num = GetMenuNum(&memberUpdateInputSMenu);
		retVal = num;
		switch (num) {
		case 1:												/* �ύX */
			ClearMemberBuffer(&mBuf);						/* �o�b�t�@���N���A */
			if (InputUpdateMember(m, &mBuf) != FALSE) {		/* �X�V���鏤�i������� */
				retVal = MemberUpdateCheckSMenu(m, &mBuf);	/* �yD-1135�z���i���ύX�m�F��� */
				if (retVal == 1) {
					num = EXIT_NUM;							/* �ύX��̓��j���[���I�� */
				}
			}
			break;
		case EXIT_NUM:										/* �߂� */
			break;
		default:											/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int MemberUpdateCheckSMenu(MEMBER *m, MEMBER *mBuf)
 * �@�\				: �yD-1126�z������ύX�m�F���
 * ���̓p�����[�^	: MEMBER *m	:�ύX�O�̉�����ւ̃|�C���^
 *					: MEMBER *mBuf	:�ύX��̉�����ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�ύX:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int MemberUpdateCheckSMenu(MEMBER *m, MEMBER *mBuf)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */

	DisplayMember(mBuf);							/* �o�^���鏤�i����\�� */
	while (num != EXIT_NUM) {
		num = GetMenuNum(&memberUpdateCheckSMenu);
		retVal = num;
		switch (num) {
		case 1:									/* �ύX */
			
			//
			//goods����R�s�y����
			//

			WriteMemberFile();					/* ���i��񃊃X�g�̃t�@�C�������� */
			printf("\n�������ύX���܂����B\n");
			num = EXIT_NUM;
			break;
		case EXIT_NUM:							/* �߂� */
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsManageMenu(void)
 * �@�\				: �yD-1130�z���i���Ǘ����j���[
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ�
 * ���L����			: �Ȃ�
 */
static int GoodsManageMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	GOODS *goods = NULL;		/* ���i���m�[�h�ւ̃|�C���^ */
	
	ReadGoodsFile(&goods);				/* ���i���t�@�C���̓Ǎ��� */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsManageMenu);
		retVal = num;
		switch(num) {
		case 1:
			GoodsRegistInputSMenu();	/* �yD-1131�z�V�K���i�����͉�� */
			break;
		case 2:
			GoodsUpdateSMenu();			/* �yD-1133�z���i���m�F��� */
			break;
		case 3:
			GoodsSortKeySMenu();		/* �yD-1137�z���i�ꗗ�\�����ڑI����� */
			break;
		case EXIT_NUM:
			break;
		default:						/* NOT REACHED */
			break;
		}
	}
	FreeGoodsList();					/* ���i��񃊃X�g�̉�� */
	return retVal;
}

/*
 * �֐���			: static int GoodsRegistInputSMenu(void)
 * �@�\				: �yD-1131�z�V�K���i�����͉��
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�o�^���Ȃ�:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int GoodsRegistInputSMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	GOODS *goods = NULL;		/* ���i���m�[�h�ւ̃|�C���^ */
	GOODS gBuf;					/* ���i��� */
	
	/* ���j���[��\������ */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsRegistInputSMenu);
		retVal = num;
		switch(num) {
		case 1:											/* ������ */
			ClearGoodsBuffer(&gBuf);					/* �o�b�t�@���N���A */
			if(InputRegistGoods(&gBuf) != FALSE) {		/* �o�^���鏤�i������� */
				num = GoodsRegistCheckSMenu(&gBuf);		/* �yD-1132�z�V�K���i���m�F��� */
			}
			break;
		case EXIT_NUM:									/* �߂� */
			break;
		default:										/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsRegistCheckSMenu(const GOODS *goods)
 * �@�\				: �yD-1132�z�V�K���i���m�F���
 * ���̓p�����[�^	: const GOODS *goods	:���i���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�o�^:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int GoodsRegistCheckSMenu(const GOODS *goods)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	
	DisplayRegistGoods(goods);					/* �o�^���鏤�i����\�� */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsRegistCheckSMenu);
		retVal = num;
		switch(num) {
		case 1:									/* �o�^ */
			RegistGoods(goods);					/* ���i�������X�g�ɓo�^ */
			WriteGoodsFile();					/* ���i��񃊃X�g�̃t�@�C�������� */
			printf("\n���i����o�^���܂����B\n");
			num = EXIT_NUM;
			break;
		case EXIT_NUM:							/* �߂� */
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsIDGetSMenu(const int size, char *id, GOODS **g)
 * �@�\				: �yD-1111�z���iID���͉�ʁi���i���t�@�C���j
 * ���̓p�����[�^	: const int size	:����
 * �o�̓p�����[�^	: char *id	:���iID
 * 					: GOODS **g	:���i���m�[�h�ւ̃|�C���^�ւ̃A�h���X
 * �߂�l			: int	:�I��ԍ��i'0'�܂���NULL�����:EXIT_NUM / ����ȊO�����:ENTER_NUM�j
 * ���L����			: ������ID����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
static int GoodsIDGetSMenu(const int size, char *id, GOODS **g)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	GOODS *search;
	
	while(TRUE) {
		DisplayTitle(&goodsIDGetSMenu);					/* �^�C�g����\�� */
		GetNumStr(id, size);							/* ID�𕶎���Ƃ��Ď擾 */
		if((id[0] == '0') && (id[1] == '\0')) {				/* ID���͂�'0'�̏ꍇ */
			retVal = EXIT_NUM;
			break;
		} else if(id[0] == '\0') {						/* ID���͂�NULL�̏ꍇ */
			retVal = EXIT_NUM;
			break;
		} else {										/* ID���͂�����ꍇ */
			/* ���i��񃊃X�g���������� */
			if(SearchGoods(id, &search) == FALSE) {
				printf("�Y�����鏤�iID������܂���B\n");
			} else {
				*g = search;
				break;
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsUpdateSMenu(void)
 * �@�\				: �yD-1133�z���i���m�F���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�߂�:EXIT_NUM / �ύX���Ȃ�:1 / �폜���Ȃ�:2�j
 * ���L����			: �Ȃ�
 */
static int GoodsUpdateSMenu(void)
{
	int retVal = ENTER_NUM;							/* �߂�l */
	int num = ENTER_NUM;							/* ���͔ԍ� */
	char id[GOODS_ID_SIZE+STRING_TERMINATOR_SIZE];	/* ���iID */
	GOODS *goods = NULL;							/* ���i���m�[�h�ւ̃|�C���^ */
	
	while(num != EXIT_NUM) {
		num = GoodsIDGetSMenu(GOODS_ID_SIZE, id, &goods);	/* �yD-1111�z���iID���͉�� */
		retVal = num;
		if(num != EXIT_NUM) {		/* �L���ȏ��iID�����͂��ꂽ��A���i���ƃ��j���[��\�� */
			DisplayGoods(goods);							/* ���i����\�� */
			num = GetMenuNum(&goodsUpdateSMenu);
			retVal = num;
			switch(num) {
			case 1:											/* �ύX */
				num = GoodsUpdateInputSMenu(goods);			/* �yD-1134�z���i���ύX��� */
				break;
			case 2:											/* �폜 */
				num = DeleteGoods(id);						/* ���i�����폜 */
				break;
			case EXIT_NUM:									/* �߂� */
				break;
			default:										/* NOT REACHED */
				break;
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsUpdateInputSMenu(GOODS* g)
 * �@�\				: �yD-1134�z���i���ύX���
 * ���̓p�����[�^	: GOODS *g:���i���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�ύX:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int GoodsUpdateInputSMenu(GOODS* g)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	GOODS gBuf;					/* ���i��� */

	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsUpdateInputSMenu);
		retVal = num;
		switch(num) {
		case 1:												/* �ύX */
			ClearGoodsBuffer(&gBuf);						/* �o�b�t�@���N���A */
			if(InputUpdateGoods(g, &gBuf) != FALSE) {		/* �X�V���鏤�i������� */
				retVal = GoodsUpdateCheckSMenu(g, &gBuf);	/* �yD-1135�z���i���ύX�m�F��� */
				if(retVal == 1){
					num = EXIT_NUM;							/* �ύX��̓��j���[���I�� */
				}
			}
			break;
		case EXIT_NUM:										/* �߂� */
			break;
		default:											/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsUpdateCheckSMenu(GOODS *g, GOODS *gBuf)
 * �@�\				: �yD-1135�z���i���ύX�m�F���
 * ���̓p�����[�^	: GOODS *g	:�ύX�O�̏��i���ւ̃|�C���^
 *					: GOODS *gBuf	:�ύX��̏��i���ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ��i�ύX:1 / �߂�:EXIT_NUM�j
 * ���L����			: �Ȃ�
 */
static int GoodsUpdateCheckSMenu(GOODS *g, GOODS *gBuf)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	
	DisplayGoods(gBuf);							/* �o�^���鏤�i����\�� */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsUpdateCheckSMenu);
		retVal = num;
		switch(num) {
		case 1:									/* �ύX */
			strncpy_s(g->title, GOODS_TITLE_SIZE+1, gBuf->title, _TRUNCATE);
			strncpy_s(g->genre, GOODS_GENRE_SIZE+1, gBuf->genre, _TRUNCATE);
			strncpy_s(g->sellDat, GOODS_SELL_DATE_SIZE+1, gBuf->sellDat, _TRUNCATE);
			strncpy_s(g->rentDat, GOODS_RENT_DATE_SIZE+1, gBuf->rentDat, _TRUNCATE);
			strncpy_s(g->lendMID, GOODS_LEND_MID_SIZE+1, gBuf->lendMID, _TRUNCATE);
			strncpy_s(g->lendSts, GOODS_LEND_STS_SIZE+1, gBuf->lendSts, _TRUNCATE);
			strncpy_s(g->lendNum, GOODS_LEND_NUM_SIZE+1, gBuf->lendNum, _TRUNCATE);
			strncpy_s(g->keep, GOODS_KEEP_SIZE+1, gBuf->keep, _TRUNCATE);
			WriteGoodsFile();					/* ���i��񃊃X�g�̃t�@�C�������� */
			printf("\n���i����ύX���܂����B\n");
			num = EXIT_NUM;
			break;
		case EXIT_NUM:							/* �߂� */
			break;
		default:								/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsSortKeySMenu(void)
 * �@�\				: �yD-1137�z���i�ꗗ�\�����ڑI�����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ�
 * ���L����			: �Ȃ�
 */
static int GoodsSortKeySMenu(void)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	GOODS *goods = NULL;		/* ���i���m�[�h�ւ̃|�C���^ */
	
	/* ���j���[��\������ */
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsSortKeySMenu);
		retVal = num;
		switch(num) {
		case 1:								/* ���iID */
			/* FALL THROUGH */
		case 2:								/* �ۊǏꏊ */
			/* FALL THROUGH */
		case 3:								/* ������ */
			/* FALL THROUGH */
		case 4:								/* �ݏo�E�ԋp�� */
			num = GoodsSortUdSMenu(num);	/* �yD-1138�z���i�ꗗ�\�����I����� */
			break;
		case EXIT_NUM:
			break;
		default:							/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsSortUdSMenu(const int key)
 * �@�\				: �yD-1138�z���i�ꗗ�\�����I�����
 * ���̓p�����[�^	: const int key	:�\�[�g�L�[
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:EXIT_NUM
 * ���L����			: �Ȃ�
 */
static int GoodsSortUdSMenu(const int key)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	
	while(num != EXIT_NUM) {
		num = GetMenuNum(&goodsSortUdSMenu);
		retVal = num;
		switch(num) {
		case 1:										/* ���� */
			/* FALL THROUGH */
		case 2:										/* �~�� */
			num = GoodsListCheckSMenu(key, num);	/* �yD-1139�z���i�ꗗ�\����� */
			retVal = EXIT_NUM;
			break;
		case EXIT_NUM:
			break;
		default:									/* NOT REACHED */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: static int GoodsListCheckSMenu(const int key, const int ud)
 * �@�\				: �yD-1139�z���i�ꗗ�\�����
 * ���̓p�����[�^	: const int key	:�\�[�g�L�[
 * 					: const int ud	:����/�~���i1:����/2:�~���j
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:EXIT_NUM
 * ���L����			: �Ȃ�
 */
static int GoodsListCheckSMenu(const int key, const int ud)
{
	int retVal = ENTER_NUM;		/* �߂�l */
	int num = ENTER_NUM;		/* ���͔ԍ� */
	
	while(num != EXIT_NUM) {
		/* ���i�ꗗ��\������ */
		if(DisplayGoodsList(key, ud, num) == FALSE) {	/* �Ō�܂ŕ\�� ? */
			num = EXIT_NUM;								/* while���𔲂��� */
			retVal = EXIT_NUM;
		} else {
			num = GetMenuNum(&goodsListCheckSMenu);		/* �I�����j���[��\������ */
			retVal = num;
		}
	}
	return retVal;
}
