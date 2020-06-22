/*
 * �t�@�C����	: common.h
 * �@�\			: ���ʂ̒�`���s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  
 */

#ifndef COMMON_H
#define COMMON_H

/* #define�}�N�� */
/* �^�U */
#define TRUE							1		/* �^ */
#define FALSE							0		/* �U */

/* ���R�[�h�I�[ */
#define REC_DELIMITER_SIZE				10		/* ���R�[�h��؂蕶������ */

/* ������I�[ */
#define STRING_TERMINATOR_SIZE			1		/* ������I�[�������� */

/* �o�b�t�@�T�C�Y */
/* GetYesNo�֐� */
#define GETYESNO_BUF_SIZE				4		/* GetYesNo�֐� ��������̓o�b�t�@�T�C�Y */

/* GetStr�֐� */
#define GETSTR_BUF_SIZE					101		/* GetStr�֐� ��������̓o�b�t�@�T�C�Y */

/* GetNumStr */
#define GETNUMSTR_BUF_SIZE				17		/* GetNumStr ��������̓o�b�t�@�T�C�Y */
	
/* GetIntStr */
#define GETINTSTR_BUF_SIZE				17		/* GetIntStr ��������̓o�b�t�@�T�C�Y */
	
/* InputYMD */
#define INPUTYMD_YEAR_BUF_SIZE			8		/* InputYMD �N�̕�������̓o�b�t�@�T�C�Y */
#define INPUTYMD_MONTH_BUF_SIZE			8		/* InputYMD ���̕�������̓o�b�t�@�T�C�Y */
#define INPUTYMD_DAY_BUF_SIZE			8		/* InputYMD ���̕�������̓o�b�t�@�T�C�Y */
#define INPUTYMD_BUF_SIZE				16		/* InputYMD  8���̓��t������i�[�p�o�b�t�@�T�C�Y */

/* GetDateStr */
#define GETDATESTR_BUF_SIZE				17		/* GetDateStr ��������̓o�b�t�@ */
	
/* IsDateStr */
#define ISDATESTR_YEAR_BUF_SIZE			8		/* IsDateStr �N�̕�����i�[�p�o�b�t�@�T�C�Y */
#define ISDATESTR_MONTH_BUF_SIZE		8		/* IsDateStr ���̕�����i�[�p�o�b�t�@�T�C�Y */
#define ISDATESTR_DAY_BUF_SIZE			8		/* IsDateStr ���̕�����i�[�p�o�b�t�@�T�C�Y */

/* ConvFormatDate */
#define CONVFORMATDATE_YEAR_BUF_SIZE	8		/* ConvFormatDate �N�̕�����i�[�p�o�b�t�@�T�C�Y */
#define CONVFORMATDATE_MONTH_BUF_SIZE	8		/* ConvFormatDate ���̕�����i�[�p�o�b�t�@�T�C�Y */
#define CONVFORMATDATE_DAY_BUF_SIZE		8		/* ConvFormatDate ���̕�����i�[�p�o�b�t�@�T�C�Y */
	
/* DiffDate */
#define DIFFDATE_YEAR_BUF_SIZE		(4 + 1)		/* DiffDate �N�̕�����i�[�p�o�b�t�@�T�C�Y */
#define DIFFDATE_MONTH_BUF_SIZE		(2 + 1)		/* DiffDate ���̕�����i�[�p�o�b�t�@�T�C�Y */
#define DIFFDATE_DAY_BUF_SIZE		(2 + 1)		/* DiffDate ���̕�����i�[�p�o�b�t�@�T�C�Y */

/* GetMenuNum */
#define GETMENUNUM_BUF_SIZE		1				/* GetMenuNum ���j���[�ԍ����̓o�b�t�@ */

/* ���t���� */
#define YEAR_SIZE				4				/* ���t������ �N */
#define MONTH_SIZE				2				/* ���t������ �� */
#define DAY_SIZE				2				/* ���t������ �� */
#define DATE_STR_SIZE			8				/* ���t������ �N���� */
#define BASE_YEAR				1900			/* ���t�֐��p��N */
#define BASE_MONTH				1				/* ���t�֐��p��� */
#define MIN_YEAR				1800			/* ���t�֐��戵�N �ŏ��l*/
#define MAX_YEAR				2100			/* ���t�֐��p���N �ő�l */
#define MIN_MONTH				1				/* ���t�֐��戵�N �ŏ��l*/
#define MAX_MONTH				12				/* ���t�֐��p���N �ő�l */
#define MIN_DAY					1				/* ���t�֐��戵�N �ŏ��l*/
#define MAX_DAY					31				/* ���t�֐��p���N �ő�l */
#define SECOND_OF_DAY			(3600 * 24)		/* ���t�֐��p 1��������̕b�� */

/* ���j���[ */
#define ENTER_NUM				99				/* ���j���[�֓���ԍ� */
#define REGIST_NUM				1				/* �A���ݏo/�ԋp�����̏I���ԍ��i�����^���j */
#define EXIT_NUM				0				/* ���j���[�𔲂���ԍ� */
#define NULL_NUM				10				/* NULL�ԍ��i�󕶎��j */
#define MENU_SEL_NUM			1				/* ���j���[�I��ԍ��̌��� */
#define MENU_NUM				10				/* ���j���[�I�����̍ő吔 */

/* ���i���t�@�C���F�ݏo�� */
#define GOODS_LEND_NO_VAL		"0"				/* �ݏo�̓����l */
#define GOODS_LEND_YES_VAL		"1"				/* �ݏo���̓����l */
#define GOODS_LEND_NO_NAME		"�ݏo��"		/* �ݏo�̕\������ */
#define GOODS_LEND_YES_NAME		"�ݏo��"		/* �ݏo���̕\������ */
#define GOODS_RET_NO_NAME		"�ԋp��"		/* �ԋp�ς̕\������ */
#define GOODS_RET_YES_NAME		"�ԋp��"		/* �ԋp���̕\������ */

/* ���i���t�@�C���F�ۊǏꏊ */
#define GOODS_KEEP_WARE_VAL		"0"				/* �q�ɂ̓����l */
#define GOODS_KEEP_SHOP_VAL		"1"				/* �X���̓����l */
#define GOODS_KEEP_WARE_NAME	"�q��"			/* �q�ɂ̕\������ */
#define GOODS_KEEP_SHOP_NAME	"�X��"			/* �X���̕\������ */

/* struct�^�O��` */
/* �^�C�g�� */
typedef struct {
	char* title;					/* �^�C�g��������ւ̃|�C���^ */
}TITLE;

/* ���j���[�I���� */
typedef struct {
	int num;						/* ���j���[�I��ԍ� */
	char* str;						/* ���j���[�I�𕶎���ւ̃|�C���^ */
}MENU_SEL;

/* ���j���[�\�� */
typedef struct {
	TITLE title;					/* �^�C�g��������ւ̃|�C���^ */
	MENU_SEL sel[MENU_NUM];			/* ���j���[�I���� */
}MENU;

/* �֐��v���g�^�C�v�錾 */
/* �����֌W */
extern int GetYesNo(const char *s);
extern void GetAnyKey(const char *s);
extern int GetStr(char *s, const int size);
extern int GetNumStr(char *s, const int size);
extern int GetIntStr(char *s, const int s1, const int s2);
extern void TrimSpace(char s[]);

/* �����֌W */
extern int GetFigure(int num);

/* ���t�֌W */
extern void InputYMD(char *date);
extern int GetDateStr(char *date);
extern void GetToday(const int y, const int m, const int d, char *date);
extern int IsDateStr(const char *date);
extern void ConvFormatDate(char *dest, const char *src);
extern int DiffDate(const char *fromdate,const char *todate);

/* ���j���[�֌W */
extern int GetMenuNum(const MENU *m);
extern void DisplayMenu(const MENU *m);
extern void DisplayTitle(const TITLE* t);

/* �����^�������֌W */
extern char *ConvLendStr(const char *s);
extern char *ConvRetStr(const char *s);
extern char *ConvKeepStr(const char *s);

#endif		/* end COMMON_H */

