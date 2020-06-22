/*
 * �t�@�C����	: common.c
 * �@�\			: ���ʂ̒�`���s��
 * ���L����		: �Ȃ�
 * �C������		:  1  2012/01/10 V01L1 ����
 *				:  2  2012/02/14 V02L1
 */

/* �w�b�_�[�̎�荞�� */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "common.h"

/* static�֐��錾 */
static int IsNumStr(const char *s, const int size);

/*
 * �֐���			: int GetYesNo(const char *s)
 * �@�\				: Y�܂���N��I������
 * ���̓p�����[�^	: const char *s		:�\������
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:Y����͂����Ƃ�TRUE / N����͂����Ƃ�FALSE
 * ���L����			: Y/N�iy/n�j�ȊO����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
int GetYesNo(const char *s)
{
	int retVal = FALSE;						/* �߂�l */
	char buf[GETYESNO_BUF_SIZE], in;
	int len;								/* ���͂���������̒��� */
	
	while(TRUE) {
		/* �^�C�g����\�� */
        printf("\n%s�iY/N�j���@", s);
		
        /* �L�[�{�[�h����̓��͂𕶎���Ƃ��Ď擾���� */
		fflush(stdin);						/* ���̓o�b�t�@���N���A */
		fgets(buf, sizeof(buf), stdin);		/* ��������� */
		len = strlen(buf);
		buf[--len] = '\0';					/* ���s�R�[�h������ */
		fflush(stdin);						/* ���͂𒴂������̕������N���A */
	
		/* ��������`�F�b�N���� */
		if(len >= 2) {						/* 2���ȏ���� */
			/* DO NOTHING */
		} else {
			in = tolower(buf[0]);			/* �p�������ɕϊ� */
			/* �������`�F�b�N���� */
			if(in == 'y') {
				retVal = TRUE;
				break;
			} else if(in == 'n') {
				retVal = FALSE;
				break;
			} else {
				/* DO NOTHING */
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: int GetStr(char *s, const int size)
 * �@�\				: ���������͂���i�ő啶�����̃`�F�b�N����j
 * ���̓p�����[�^	: const int size	:���͂ł��镶�����i�������`�F�b�N���Ȃ��Ƃ���0�j
 * �o�̓p�����[�^	: char *s	:������
 * �߂�l			: int		:���͂��ꂽ������
 * ���L����			: 100�����i���p�j�𒴂��镔���͖�������
 */
int GetStr(char *s, const int size)
{
	char buf[GETSTR_BUF_SIZE];				/* ��������̓o�b�t�@ */
	int len;								/* ���͂���������̒��� */
	
	while(TRUE) {
		/* �L�[�{�[�h����̓��͂𕶎���Ƃ��Ď擾���� */
		fflush(stdin);						/* ���̓o�b�t�@���N���A */
		fgets(buf, sizeof(buf), stdin);		/* ��������� */
		len = strlen(buf);
		buf[--len] = '\0';					/* ���s�R�[�h������ */
		fflush(stdin);						/* ���͂𒴂������̕������N���A */
		
		/* ��������`�F�b�N���� */
		if((size > 0) && (len > size)) {	/* �w�蕶�����𒴉� */
			printf("%d�����i���p�j�ȓ��œ��͂��Ă��������B\n", size);
			printf("���́��@");
		} else {
			strncpy_s(s, len+1, buf, _TRUNCATE);	/* s�ɕ�������Z�b�g */
			break;
		}
	}
	return len;
}

/*
 * �֐���			: int GetNumStr(char *s, const int size)
 * �@�\				: �w�茅���i1�`16���j�̐����݂̂̕��������͂���
 * ���̓p�����[�^	: const int size	:����
 * �o�̓p�����[�^	: char *s			:������
 * �߂�l			: int	:TRUE�i�w�茅������́j/FALSE�i0,1�̂ݓ��́j
 * ���L����			: �����ȊO����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
int GetNumStr(char *s, const int size)
{
	int retVal = TRUE;
	char buf[GETNUMSTR_BUF_SIZE];		/* ��������̓o�b�t�@ */
	int len;							/* ���͂���������̒��� */
	
	while(TRUE) {
		/* �L�[�{�[�h����̓��͂𕶎���Ƃ��Ď擾���� */
		fflush(stdin);						/* ���̓o�b�t�@���N���A */
		fgets(buf, sizeof(buf), stdin);		/* ��������� */
		len = strlen(buf);
		buf[--len] = '\0';					/* ���s�R�[�h������ */
		fflush(stdin);						/* ���͂𒴂������̕������N���A */
		
		/* ��������`�F�b�N���� */
		if(len == 0) {									/* �G���^�[�L�[�̂� */
			s[0] = '\0';
			retVal = FALSE;
			break;
		} else if((len == 1) && (buf[0] == '1')) {		/* 1����� */
			strncpy_s(s, size+1, buf, _TRUNCATE);
			retVal = FALSE;
			break;
		} else if((len == 1) && (buf[0] == '0')) {		/* 0����� */
			strncpy_s(s, size+1, buf, _TRUNCATE);
			retVal = FALSE;
			break;
		} else if(len != size) {						/* �w�茅���ȊO */
			printf("%d���œ��͂��Ă��������B\n", size);
			printf("���́��@");
		} else if(IsNumStr(buf, len) == FALSE) {		/* �����ȊO�̕��������� */
			printf("��������͂��Ă��������B\n");
			printf("���́��@");
		} else {
			strncpy_s(s, size+1, buf, _TRUNCATE);
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: int GetIntStr(char *s, const int s1, const int s2)
 * �@�\				: �w��l1�ȏ�w��l2�ȉ��̐�������͂���
 * ���̓p�����[�^	: const int s1	:�ŏ��l
 * 					: const int s2	:�ő�l
 * 					:				 �������A�Ƃ���0���w�肵���ꍇ�ɂ͒l�͈̔̓`�F�b�N�͂��Ȃ�
 * �o�̓p�����[�^	: char *s	:������
 * �߂�l			: int	:TRUE�i������́j/FALSE�i�󕶎�(Enter�̂�)���́j
 * ���L����			: �����ȊO����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
int GetIntStr(char *s, const int s1, const int s2)
{
	int retVal = TRUE;
	char buf[GETINTSTR_BUF_SIZE];		/* ��������̓o�b�t�@ */
	int len;							/* ���͂���������̒��� */
	int val;							/* ������𐔒l�ɕϊ������l */
	
	while(TRUE) {
		/* �L�[�{�[�h����̓��͂𕶎���Ƃ��Ď擾���� */
		fflush(stdin);						/* ���̓o�b�t�@���N���A */
		fgets(buf, sizeof(buf), stdin);		/* ��������� */
		len = strlen(buf);
		buf[--len] = '\0';					/* ���s�R�[�h������ */
		fflush(stdin);						/* ���͂𒴂������̕������N���A */
		
		/* ��������`�F�b�N���� */
		if(len != 0) {
			if(IsNumStr(buf, len) == FALSE) {				/* �����ȊO�̕��������� ? */
				printf("��������͂��Ă��������B\n");
				printf("���́��@");
			} else {
				val = atoi(buf);
				if((s1 == 0) && (s2 == 0)) {				/* ���l�͈̔̓`�F�b�N�����Ȃ� */
					strncpy_s(s, len+1, buf, _TRUNCATE);	/* s�ɕ�������Z�b�g */
					retVal = TRUE;
					break;
				} else if((val >= s1) && (val <= s2)) {		/* ���͂��͈͓� */
					strncpy_s(s, len+1, buf, _TRUNCATE);	/* s�ɕ�������Z�b�g */
					retVal = TRUE;
					break;
				} else {
					printf("���l���͈͊O�ł��B\n");
					printf("���́��@");
				}
			}
		} else {
			s[0] = '\0';
			retVal = FALSE;									/* ���͂Ȃ��̏ꍇ */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: void TrimSpace(char s[])
 * �@�\				: ������̖����̋󔒂��폜����
 * ���̓p�����[�^	: char *s	:�󔒂̓�����������
 * �o�̓p�����[�^	: char *s	:�󔒂�������������
 * �߂�l			: �Ȃ�
 * ���L����			: ������̖�������폜����
 */
void TrimSpace(char s[])
{
	int i;
	
	i = strlen(s) - 1;
	while(i >= 0) {
		if(s[i] == ' ') {
			s[i] = '\0';
			i--;
		} else {
			break;
		}
	}
}

/*
 * �֐���			: int GetFigure(int num)
 * �@�\				: �����̌������擾����
 * ���̓p�����[�^	: int num	:����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:����
 * ���L����			: �Ȃ�
 */
int GetFigure(int num)
{
    int i = 1;
	
	num = num / 10;
	while(num != 0) {
		num = num / 10;
		i++;
	}
    return i;
}

/*
 * �֐���			: void InputYMD(char *date)
 * �@�\				: ���t��N�������Ƃɓ��͂��A��肪�Ȃ����`�F�b�N����
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: char *date	:���t
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void InputYMD(char *date)
{
	char sy[INPUTYMD_YEAR_BUF_SIZE];		/* �N */
	char sm[INPUTYMD_MONTH_BUF_SIZE];		/* �� */
	char sd[INPUTYMD_DAY_BUF_SIZE];			/* �� */
	char buf[INPUTYMD_BUF_SIZE];			/* 8���̓��t */
	
	while(TRUE) {
		/* �N����͂��� */
		printf("�N�i����j���@");
		GetIntStr(sy, MIN_YEAR, MAX_YEAR);
		
		/* ������͂��� */
		printf("���@�@�@�@���@");
		GetIntStr(sm, MIN_MONTH, MAX_MONTH);
		
		/* ������͂��� */
		printf("���@�@�@�@���@");
		GetIntStr(sd, MIN_DAY, MAX_DAY);
		
		/* ���t���`�F�b�N���� */
		sprintf_s(buf, INPUTYMD_BUF_SIZE, "%04d%02d%02d", atoi(sy), atoi(sm), atoi(sd));
		if(IsDateStr(buf) == FALSE) {
			printf("���t�̓��͂Ɍ�肪����܂��B�N�i����j����ēx���͂��Ă��������B\n");
		} else {
			strncpy_s(date, DATE_STR_SIZE+1, buf, _TRUNCATE);
			break;
		}
	}
}

/*
 * �֐���			: int GetDateStr(char *date)
 * �@�\				: ���t�iYYYYMMDD�j����͂���
 * ���̓p�����[�^	: �Ȃ�
 * �o�̓p�����[�^	: char *date	:������
 * �߂�l			: int	:TRUE�i������́j/FALSE�i�󕶎�(Enter�̂�)���́j
 * ���L����			: ���t�ȊO�̐�������͂����ꍇ�ɂ͍ē��͂𑣂�
 */
int GetDateStr(char *date)
{
	int retVal = TRUE;
	char buf[GETDATESTR_BUF_SIZE];		/* ��������̓o�b�t�@ */
	int len;							/* ���͂���������̒��� */
	
	while(TRUE) {
		/* �L�[�{�[�h����̓��͂𕶎���Ƃ��Ď擾���� */
		fflush(stdin);						/* ���̓o�b�t�@���N���A */
		fgets(buf, sizeof(buf), stdin);		/* ��������� */
		len = strlen(buf);
		buf[--len] = '\0';					/* ���s�R�[�h������ */
		fflush(stdin);						/* ���͂𒴂������̕������N���A */
		
		/* ��������`�F�b�N���� */
		if(len != 0) {
			if(IsNumStr(buf, len) == FALSE) {					/* �����ȊO���`�F�b�N */
				printf("��������͂��Ă��������B\n");
				printf("���́��@");
			} else if(IsDateStr(buf) == FALSE) {				/* ���t�͈̔͂��`�F�b�N */
				printf("���t���͈͊O�ł��B\n");
				printf("���́��@");
			} else {
				strncpy_s(date, DATE_STR_SIZE+1, buf, _TRUNCATE);	/* date�ɕ�������Z�b�g */
				break;
			}
		} else {
			date[0] = '\0';
			retVal = FALSE;										/* ���͂Ȃ��̏ꍇ */
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: void GetToday(const int y, const int m, const int d, char *date)
 * �@�\				: ���݂̓��t�Ɏw�肵�������������Z������������擾����
 * ���̓p�����[�^	: const int y	:�����Z����N
 * 					: const int m	:�����Z���錎
 * 					: const int d	:�����Z�����
 * �o�̓p�����[�^	: char *date	:���t�iYYYYMMDD�j
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void GetToday(const int y, const int m, const int d, char *date)
{
	time_t tNow, tCal;
	struct tm tmDate;
	
	/* ���݂̓��t���擾���� */
	tNow = time(NULL);
	localtime_s(&tmDate, &tNow);
	
	/* �w�肵�����������Z�������t���擾���� */
	tmDate.tm_year += y;			/* �N�����Z */
	tmDate.tm_mon += m;				/* �������Z */
	tmDate.tm_mday += d;			/* �������Z */
	tCal = mktime(&tmDate);			/* ���t�𐮌` */
	localtime_s(&tmDate, &tCal);	/* �\���p�ɔN�����𕪊� */
	
	/* ���t��N�����ʂɕ�����Ƃ��Ď擾���� */
	sprintf_s(date, DATE_STR_SIZE+1, "%04d%02d%02d", tmDate.tm_year + BASE_YEAR, tmDate.tm_mon + BASE_MONTH, tmDate.tm_mday);
}

/*
 * �֐���			: int IsDateStr(const char *date)
 * �@�\				: ���t���`�F�b�N����
 * ���̓p�����[�^	: const char *date	:YYYYMMDD�`���̕�����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE/FALSE
 * ���L����			: 1970�N�����͖����Ƃ���
 */
int IsDateStr(const char *date)
{
	int retVal;
	const int dayTbl[] = {	/* �e���̌����� */
		31,						/* 1���̌����� */
		29,						/* 2���̌����� �i�[�N���܂ށj*/
		31,						/* 3���̌����� */
		30,						/* 4���̌����� */
		31,						/* 5���̌����� */
		30,						/* 6���̌����� */
		31,						/* 7���̌����� */
		31,						/* 8���̌����� */
		30,						/* 9���̌����� */
		31,						/* 10���̌����� */
		30,						/* 11���̌����� */
		31						/* 12���̌����� */
	};
	char sy[ISDATESTR_YEAR_BUF_SIZE];		/* �N */
	char sm[ISDATESTR_MONTH_BUF_SIZE];		/* �� */
	char sd[ISDATESTR_DAY_BUF_SIZE];		/* �� */
	int iy, im, id;
	
	if(strlen(date) != DATE_STR_SIZE) {						/* ���������`�F�b�N */
		retVal = FALSE;
	} else {
		strncpy_s(sy, ISDATESTR_YEAR_BUF_SIZE, date, YEAR_SIZE);
		strncpy_s(sm, ISDATESTR_MONTH_BUF_SIZE, date+YEAR_SIZE, MONTH_SIZE);
		strncpy_s(sd, ISDATESTR_DAY_BUF_SIZE, date+YEAR_SIZE+MONTH_SIZE, DAY_SIZE);
		iy = atoi(sy);
		im = atoi(sm);
		id = atoi(sd);
		if((im < MIN_MONTH) || (im > MAX_MONTH)){				/* �����͈̔͂��`�F�b�N */
			retVal = FALSE;
		} else if((id < MIN_DAY) || (id > MAX_DAY)) {			/* �����͈̔͂��`�F�b�N */
			retVal = FALSE;
		} else if(id > dayTbl[im-1]) {							/* �����͈̔͂��`�F�b�N */
			retVal = FALSE;
		} else {
			retVal = TRUE;
		}
		if((iy % 4) != 0) {								/* �[�N���`�F�b�N �N��4�Ŋ���؂�Ȃ��Ƃ� */
			if((im == 2) && (id == 29)) {				/* �[�N�łȂ��� 2��29���̓G���[ */
				retVal = FALSE;
			}
		}
	}
	return retVal;
}

/*
 * �֐���			: void ConvFormatDate(char *dest, const char *src)
 * �@�\				: ���t������ɃX���b�V����}������
 * ���̓p�����[�^	: const char *src	:���͕�����
 * �o�̓p�����[�^	: char *dest		:�o�͕�����
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void ConvFormatDate(char *dest, const char *src)
{
	char y[CONVFORMATDATE_YEAR_BUF_SIZE];			/* �N */
	char m[CONVFORMATDATE_MONTH_BUF_SIZE];			/* �� */
	char d[CONVFORMATDATE_DAY_BUF_SIZE];			/* �� */
	
	strncpy_s(y, CONVFORMATDATE_YEAR_BUF_SIZE, src, YEAR_SIZE);
	strncpy_s(m, CONVFORMATDATE_MONTH_BUF_SIZE, src+YEAR_SIZE, MONTH_SIZE);
	strncpy_s(d, CONVFORMATDATE_DAY_BUF_SIZE, src+YEAR_SIZE+MONTH_SIZE, DAY_SIZE);
	sprintf_s(dest, YEAR_SIZE+MONTH_SIZE+DAY_SIZE+3, "%s/%s/%s", y, m, d);
}

/*
 * �֐���			: int DiffDate(const char *fromdate,const char *toDate)
 * �@�\				: ftomdate �� toDate �̓�̓��t�Ԋu������ŕԂ�
 * ���̓p�����[�^	: char *fromdate:���t�iYYYYMMDD�j������
 * 					: char *tomdate :���t�iYYYYMMDD�j������
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int			:2�̓��t�Ԋu�̓��� �A�p�����[�^�G���[�̎��͏�� 0
 * ���L����			: fromDate > toDate �̏ꍇ�͕��̒l��Ԃ�
 *					: 1970�N�����͖����Ƃ���
 */
int DiffDate(const char *fromDate,const char *toDate)
{
	struct tm tmFrom,tmTo;					/* ���̓p�����[�^�̃J�����_�[�l�i�[�p tm�����\���� */
	char sYear[DIFFDATE_YEAR_BUF_SIZE];		/* �N */
	char sMonth[DIFFDATE_MONTH_BUF_SIZE];	/* �� */
	char sDay[DIFFDATE_DAY_BUF_SIZE];		/* �� */
	int DateInterval;						/* �����ł̊Ԋu�i�[�p */

	if(IsDateStr(fromDate) && IsDateStr(toDate)){			/* ���̓p�����[�^�̊m�F */
		/* fromDate��tm�\���̂Ɋi�[ */
		strncpy_s(sYear, DIFFDATE_YEAR_BUF_SIZE, fromDate, YEAR_SIZE);						/* �N�����o�� */
		strncpy_s(sMonth, DIFFDATE_MONTH_BUF_SIZE, fromDate+YEAR_SIZE, MONTH_SIZE);			/* �������o�� */
		strncpy_s(sDay, DIFFDATE_DAY_BUF_SIZE, fromDate+YEAR_SIZE+MONTH_SIZE, DAY_SIZE);	/* �������o�� */
		tmFrom.tm_year = atoi(sYear) - BASE_YEAR;				/* �N���Z�b�g */
		tmFrom.tm_mon = atoi(sMonth) - BASE_MONTH;				/* �����Z�b�g */
		tmFrom.tm_mday = atoi(sDay);							/* �����Z�b�g */
		tmFrom.tm_hour = 0;										/* ����0���Z�b�g */
		tmFrom.tm_min = 0;										/* ����0���Z�b�g */
		tmFrom.tm_sec = 0;										/* �b��0���Z�b�g */
		tmFrom.tm_isdst = 0;									/* �Ď��Ԃ͎g�p���Ȃ�*/
		/* toDate��tm�\���̂Ɋi�[ */
		strncpy_s(sYear, YEAR_SIZE+1, toDate, YEAR_SIZE);						/* �N�����o�� */
		strncpy_s(sMonth, MONTH_SIZE+1, toDate+YEAR_SIZE, MONTH_SIZE);			/* �������o�� */
		strncpy_s(sDay, DAY_SIZE+1, toDate+YEAR_SIZE+MONTH_SIZE, DAY_SIZE);	/* �������o�� */
		tmTo.tm_year = atoi(sYear) - BASE_YEAR;					/* �N���Z�b�g */
		tmTo.tm_mon = atoi(sMonth) - BASE_MONTH;				/* �����Z�b�g */
		tmTo.tm_mday = atoi(sDay);								/* �����Z�b�g */
		tmTo.tm_hour = 0;										/* ����0���Z�b�g */
		tmTo.tm_min = 0;										/* ����0���Z�b�g */
		tmTo.tm_sec = 0;										/* �b��0���Z�b�g */
		tmTo.tm_isdst = 0;										/* �Ď��Ԃ͎g�p���Ȃ�*/
		DateInterval =  (int)(mktime(&tmTo) - mktime(&tmFrom)) / (SECOND_OF_DAY);	/* �b����������֕ϊ� */
	} else {
		DateInterval = 0;										/* �p�����[�^�G���[�̎��͏�� 0 ��Ԃ� */
	}
	return DateInterval;
}

/*
 * �֐���			: static int IsNumStr(const char *s, const int size)
 * �@�\				: �����������݂̂��`�F�b�N����
 * ���̓p�����[�^	: const char *s		:������
 * 					: const int size	:����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:TRUE/FALSE
 * ���L����			: �Ȃ�
 */
static int IsNumStr(const char *s, const int size)
{
	int retVal = TRUE;
	int i;
	
	for(i=0; i<size; i++) {
		if((s[i] < '0') || (s[i] > '9')) {
			retVal = FALSE;
			break;
		}
	}
	return retVal;
}

/*
 * �֐���			: int GetMenuNum(const MENU *m)
 * �@�\				: ���j���[��\�����A�I���������j���[�ԍ���Ԃ�
 * ���̓p�����[�^	: const MENU *m	�FMENU�^�\���̕ϐ��ւ̃A�h���X
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: int	:�I��ԍ�
 * ���L����			: ���j���[�ɂȂ��ԍ�����͂����ꍇ�ɂ͍ē��͂𑣂�
 */
int GetMenuNum(const MENU *m)
{
	int i, in;
	char buf[GETMENUNUM_BUF_SIZE+STRING_TERMINATOR_SIZE];	/* ���j���[�ԍ����̓o�b�t�@ */
	
	/* �I��ԍ����擾���� */
	do {
		DisplayMenu(m);							/* ���j���[��ʂ�\�� */
		/* �I��ԍ�����͂��� */
		GetNumStr(buf, GETMENUNUM_BUF_SIZE);	/* �ԍ��𕶎���Ƃ��Ď擾 */
		if(buf[0] == '\0') {					/* ���͂��G���^�[�L�[�݂̂̏ꍇ */
			in = NULL_NUM;						/* NULL�ԍ��i�󕶎��j��ݒ� */
		} else {								/* ID���͂�����ꍇ */
			in = atoi(buf);						/* ���l�ɕϊ� */
			for(i = 0; i < MENU_NUM; i++) {
				/* ���͔ԍ����I��ԍ��Ɠ������Ȃ��for���𔲂��� */
				if(m->sel[i].num == in) {
					break;
				}
			}
			/* ���͔ԍ����I��ԍ��Ɠ������Ȃ��while���𔲂��� */
			if(i == MENU_NUM) {
				printf("�I��ԍ����قȂ�܂��B\n");
			}
		}
	} while((i == NULL_NUM) || (i == MENU_NUM));
	
	return in;									/* ���͔ԍ���Ԃ� */
}

/*
 * �֐���			: void DisplayMenu(const MENU *m)
 * �@�\				: ���j���[��\������
 * ���̓p�����[�^	: const MENU *m	�FMENU�^�\���̕ϐ��ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayMenu(const MENU *m)
{
	int i;
	
	printf("%s\n", m->title);
	for(i = 0; (i < MENU_NUM) && (m->sel[i].str != NULL); i++) {
		printf("%d:%s\n", m->sel[i].num, m->sel[i].str);
	}
	printf("���́��@");
}

/*
 * �֐���			: void DisplayTitle(const TITLE *t)
 * �@�\				: �^�C�g����\������
 * ���̓p�����[�^	: const TITLE *t	�FTITLE�^�\���̕ϐ��ւ̃|�C���^
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: �Ȃ�
 * ���L����			: �Ȃ�
 */
void DisplayTitle(const TITLE *t)
{
	printf("\n%s", t->title);
}

/*
 * �֐���			: char *ConvLendStr(const char *s)
 * �@�\				: �ݏo�󋵂̕\��������i�ݏo��/�ݏo���j�ɕϊ�����
 * ���̓p�����[�^	: const char *s	:0/1�̕�����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: char *dsp		:�ݏo�󋵂̕�����i�ݏo��/�ݏo���j
 * ���L����			: �Ȃ�
 */
char *ConvLendStr(const char *s)
{
	static const char *tbl[] = {GOODS_LEND_NO_NAME, GOODS_LEND_YES_NAME};
	char *dsp;
	
	if((*s == '0') || (*s == '1')) {
		dsp = (char *)tbl[atoi(s)];
	} else {
		dsp = "�Q�Q�Q";
	}
	return dsp;
}

/*
 * �֐���			: char *ConvRetStr(const char *s)
 * �@�\				: �ԋp�󋵂̕\��������i�ԋp��/�ԋp�ρj�ɕϊ�����
 * ���̓p�����[�^	: const char *s	:0/1�̕�����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: char *dsp		:�ԋp�󋵂̕�����i�ԋp��/�ԋp�ρj
 * ���L����			: �Ȃ�
 */
char *ConvRetStr(const char *s)
{
	static const char *tbl[] = {GOODS_RET_NO_NAME, GOODS_RET_YES_NAME};
	char *dsp;
	
	if((*s == '0') || (*s == '1')) {
		dsp = (char *)tbl[atoi(s)];
	} else {
		dsp = "�Q�Q�Q";
	}
	return dsp;
}

/*
 * �֐���			: char *ConvKeepStr(const char *s)
 * �@�\				: �ۊǏꏊ�̕\��������i�q��/�X���j�ɕϊ�����
 * ���̓p�����[�^	: const char *s	:0/1�̕�����
 * �o�̓p�����[�^	: �Ȃ�
 * �߂�l			: char *dsp		:�ۊǏꏊ�̕�����i�q��/�X���j
 * ���L����			: �Ȃ�
 */
char *ConvKeepStr(const char *s)
{
	static const char *tbl[] = {GOODS_KEEP_WARE_NAME, GOODS_KEEP_SHOP_NAME};
	char *dsp;
	
	if((*s == '0') || (*s == '1')) {
		dsp = (char *)tbl[atoi(s)];
	} else {
		dsp = "�Q�Q";
	}
	return dsp;
}
