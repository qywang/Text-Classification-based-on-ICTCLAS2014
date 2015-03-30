// win_cDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "../../include/NLPIR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
 using namespace std ;
#ifndef OS_LINUX
#pragma comment(lib, "../lib/NLPIR.lib")
#endif

//Linux
#ifdef OS_LINUX
	#define _stricmp(X,Y) strcasecmp((X),(Y))
	#define _strnicmp(X,Y,Z) strncasecmp((X),(Y),(Z))
	#define strnicmp(X,Y,Z)	strncasecmp((X),(Y),(Z))
	#define _fstat(X,Y)     fstat((X),(Y))
	#define _fileno(X)     fileno((X))
	#define _stat           stat
	#define _getcwd         getcwd
	#define _off_t          off_t
	#define PATH_DELEMETER  "/"
#else
	#pragma warning(disable:4786)
	#define PATH_DELEMETER  "\\"
#endif
//void SplitGBK(const char *sInput);
//void SplitBIG5();
//void SplitUTF8();
//void testNewWord();
struct Keywords_Stat //ͳ�ƴ�Ƶ
{
	string s;
	int keyword_freq;//��Ƶ
	int libnum[11];//������һ��
};
Keywords_Stat Keywords[100];
int keyword_num=0;//�ؼ��ʸ���
int word_num=0;//�����ܴ���
double LIB[11]={0};//�ؼ�����ÿ���ʿ��г��ֵ��ܴ���

void testWord(int nCode)
{
	//��ʼ���ִ����
	if(!NLPIR_Init("..",nCode))//�����ڵ�ǰ·���£�Ĭ��ΪGBK����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	char sInputFile[1024]="../test/test.TXT",sResultFile[1024];
	//if (nCode==UTF8_CODE)
	//{
		//strcpy(sInputFile,"../test/test-utf8.TXT");
	//}

	//NLPIR
	const char *sResult=NLPIR_GetFileKeyWords(sInputFile);//��ȡ�ؼ��ʣ�����Result.txt��
	FILE *fp=fopen("Result.txt","wb");
	fprintf(fp,sResult);
	fclose(fp);
	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result1.txt");
	NLPIR_FileProcess(sInputFile,sResultFile);//�ִʣ�����test.TXT_result1.txt��

	ifstream fin1("Result.txt");
	char c[20];
	
	int i=0,j=0;
	string s_key,s2;
    fin1>>s_key;
	cout<<endl<<"�ؼ���:"<<endl;
	const char*s=s_key.c_str();
	while (s[i]!='\0')
	{
		j=0;
		while(s[i]!='#')
		{
			c[j]=s[i];
			j++;i++;
		}
		c[j]='\0';
		Keywords[keyword_num].s=c;
		cout<<Keywords[keyword_num].s<<"  ";
		i++;keyword_num++;
	}
	cout<<keyword_num<<endl;
	fin1.close();
	fin1.clear();
	ifstream fin2(sResultFile);
	string Total_Words[500];
	i=0;j=0;
	cout<<endl<<"�ִʽ��:"<<endl;
	while( fin2 >> s2 ) 
    {  
       s=s2.c_str();
	   if(s[3]!='w'&&s[2]!='w')//ȥ��������
	   {
			while(s[i]!='/')
			{
				c[j]=s[i];
				j++;i++;
			}
			c[j]='\0';
			Total_Words[word_num]=c;
			
			cout<<Total_Words[word_num]<<"  ";
			j=0;i=0;word_num++;
	   }
    }
	cout<<endl<<"��Ƶͳ�ƽ����"<<endl;
	fin2.close();
	fin2.clear();
	i=0;j=0;
	for(i=0;i<=keyword_num-1;i++)
	{
		Keywords[i].keyword_freq=0;
		for(j=0;j<=word_num-1;j++)
			if(Keywords[i].s==Total_Words[j])
				Keywords[i].keyword_freq++;
	}
	for(i=0;i<=keyword_num-1;i++)
		cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<" ";
	cout<<endl;

   //fp=fopen("ResultNew.txt","wb");
   
    
	//int totalwordcount=NLPIR_GetParagraphProcessAWordCount(sResultFile);
	//cout<<totalwordcount<<endl;
	//s=s2.c_str();
	/*string word[500];
    i=0;j=0;k=0;
	while (s[i]!='\0')
	{
		j=0;
		while(s[i] & 0x80)
		{
			c[j]=s[i];
			j++;i++;
		}
		c[j]='\0';
		word[k]=c;
		cout<<word[k]<<endl;
		while(!s[i] & 0x80)
		{i++;}
		k++;
	}
	//fin2.close();
	//fin2.clear();*/
	/*for(int i=0; s[i] != '\0'; i++)
    {
        if(!(s[i] & 0x80))
        {   
            printf("this is a char:%c\n",s[i]);
        }
        else //���ı���
        {
            char w[2];//���ַ�������ʽ�洢����
            w[0] = s[i];
            w[1] = s[i+1];       
            printf("this is a chinese:%2s\n",w);
            i++;
        }
    }*/
  
	//cout<<wcount<<endl;
	
	//sResult=NLPIR_GetFileNewWords(sInputFile);
	//fp=fopen("ResultNew.txt","wb");
	//fprintf(fp,sResult);
	//fclose(fp);

	//NLPIR_NWI_Start();
	//NLPIR_NWI_AddFile(sInputFile);
	//NLPIR_NWI_Complete();
	//const char *pNewWordlist=NLPIR_NWI_GetResult();
	//printf("ʶ������´�Ϊ��%s\n",pNewWordlist);

	

	//NLPIR_NWI_Result2UserDict();//�´�ʶ����

	//strcpy(sResultFile,sInputFile);
	//strcat(sResultFile,"_result2.txt");
	//NLPIR_FileProcess(sInputFile,sResultFile);

	NLPIR_Exit();
}

void KW_Topic_Classify()
{
	int i=0,j=0;
	string s_temp1,s_temp2,s_temp3,s_temp4,s_temp5,s_temp6,s_temp7,s_temp8,s_temp9,s_temp10;
    cout<<keyword_num;
	ifstream fin1("�ʿ�һ-����.txt");
	ifstream fin2("�ʿ��-ҽ�Ʊ���.txt");
	ifstream fin3("�ʿ���-����.txt");
	ifstream fin4("�ʿ���-����.txt");
	ifstream fin5("�ʿ���-����.txt");
	ifstream fin6("�ʿ���-����.txt");
	ifstream fin7("�ʿ���-�Ƽ�.txt");
	ifstream fin8("�ʿ��-����.txt");
	ifstream fin9("�ʿ��-�ƾ�.txt");
	ifstream fin10("�ʿ�ʮ-�����Ļ�.txt");
	
	fin1>>s_temp1;fin1.close();fin1.clear();
	fin2>>s_temp2;fin2.close();fin2.clear();
	fin3>>s_temp3;fin3.close();fin3.clear();
	fin4>>s_temp4;fin4.close();fin4.clear();
	fin5>>s_temp5;fin5.close();fin5.clear();
	fin6>>s_temp6;fin6.close();fin6.clear();
	fin7>>s_temp7;fin7.close();fin7.clear();
	fin8>>s_temp8;fin8.close();fin8.clear();
	fin9>>s_temp9;fin9.close();fin9.clear();
	fin10>>s_temp10;fin10.close();fin10.clear();
	cout<<"�������ʴʿ���������£�"<<endl;
	//cout<<endl<<s_temp8<<endl;
	
	for(i=0;i<=keyword_num-1;i++)
	{
		Keywords[i].libnum[0]=1;//�ʿ���û�иô�
		if (s_temp1.find(Keywords[i].s)!=string::npos&&s_temp1.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[1]=1;
			Keywords[i].libnum[0]=0;
			LIB[1]=LIB[1]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[1]=0;
		if (s_temp2.find(Keywords[i].s)!=string::npos&&s_temp2.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[2]=1;
			Keywords[i].libnum[0]=0;
			LIB[2]=LIB[2]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[2]=0;
		if (s_temp3.find(Keywords[i].s)!=string::npos&&s_temp3.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[3]=1;
			Keywords[i].libnum[0]=0;
			LIB[3]=LIB[3]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[3]=0;
		if (s_temp4.find(Keywords[i].s)!=string::npos&&s_temp4.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[4]=1;
			Keywords[i].libnum[0]=0;
			LIB[4]=LIB[4]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[4]=0;
		if (s_temp5.find(Keywords[i].s)!=string::npos&&s_temp5.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[5]=1;
			Keywords[i].libnum[0]=0;
			LIB[5]=LIB[5]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[5]=0;
		if (s_temp6.find(Keywords[i].s)!=string::npos&&s_temp6.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[6]=1;
			Keywords[i].libnum[0]=0;
			LIB[6]=LIB[6]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[6]=0;
		if (s_temp7.find(Keywords[i].s)!=string::npos)//&&s_temp7.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[7]=1;
			Keywords[i].libnum[0]=0;
			LIB[7]=LIB[7]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[7]=0;
		if (s_temp8.find(Keywords[i].s)!=string::npos&&s_temp8.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[8]=1;
			Keywords[i].libnum[0]=0;
			//cout<<Keywords[i].s<<":"<<s_temp8.find(Keywords[i].s);
			LIB[8]=LIB[8]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[8]=0;
		if (s_temp9.find(Keywords[i].s)!=string::npos&&s_temp9.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[9]=1;
			Keywords[i].libnum[0]=0;
			LIB[9]=LIB[9]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[9]=0;
		if (s_temp10.find(Keywords[i].s)!=string::npos&&s_temp10.find(Keywords[i].s)%2==0)
		{
			Keywords[i].libnum[10]=1;
			Keywords[i].libnum[0]=0;
			LIB[10]=LIB[10]+Keywords[i].keyword_freq;
		}
		else
			Keywords[i].libnum[10]=0;
	}
	for(i=0;i<=10;i++)
		cout<<LIB[i]<<"  ";
	for(i=0;i<=keyword_num-1;i++)
	{
		if(Keywords[i].libnum[0]==1)
			cout<<Keywords[i].s<<":�ʿ����޸ôʣ�";
		else
		{
			cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<"  :���ڴʿ�";
			for(j=0;j<=10;j++)
				if(Keywords[i].libnum[j]==1)
					cout<<j;
		}
		cout<<endl;
	}
}

int NaiveBayes(int doc,int ccount[],int total)
{
	double p1=0,p_temp=0,bayes_temp=0,numerator,denominator;
	int i=0,cl=0;
	double test=pow(2,(double)10);
	cout<<test;
	
	for(i=1;i<=doc;i++)
	{
		numerator=pow(2,LIB[i]);
	    denominator=pow(total+ccount[i-1],(double)keyword_num);
		//cout<<"ccount[i-1]:"<<ccount[i-1];
		cout<<"total+ccount[i-1]:"<<total+ccount[i-1];
		bayes_temp=numerator/denominator;
		cout<<"numerator:"<<numerator<<"/"<<"denominator:"<<denominator<<"="<<bayes_temp;
		p_temp=(double)ccount[i-1]/(double)total;//�������
		cout<<"      ccount[i-1]:"<<ccount[i-1]<<"/"<<"total:"<<total<<"="<<p_temp;
		p_temp=p_temp*bayes_temp;
		
		if(p_temp>p1)
		{
			if((doc==2)&&(p_temp/p1<=10))//�ж��������
				cl=3;
			else
			{
				p1=p_temp;
				cl=i;
			}
		}
		else
			if((doc==2)&&(p1/p_temp<=10))//�ж��������
				cl=3;
		cout<<"    "<<i<<":"<<p_temp<<endl;
	}
	//cout<<numerator<<"/"<<denominator<<"="<<p1;
	cout<<"�����������"<<cl<<endl;
	return cl;
}

void KW_Emo_Classify()
{
	int i=0,j=0;
	string s_temp1,s_temp2,s_temp3,s_temp4,s_temp5,s_temp6,s_temp7,s_temp8,s_temp9,s_temp10;
	ifstream fin1("һ-���ĸ������۴���.txt");
	//ifstream fin2("��-���ĸ�����д���.txt");
	ifstream fin2("��-�����������۴���.txt");
	//ifstream fin4("��-����������д���.txt");
	//ifstream fin3("��-���Դ���.txt");
	
	fin1>>s_temp1;fin1.close();fin1.clear();
	fin2>>s_temp2;fin2.close();fin2.clear();
	//fin3>>s_temp3;fin3.close();fin3.clear();
	cout<<"������дʿ���������£�"<<endl;
    LIB[1]=LIB[2]=LIB[3]=0;
	
	for(i=0;i<=keyword_num-1;i++)
	{
		//Keywords[i].s="��"+Keywords[i].s+"��";
		Keywords[i].libnum[0]=1;//�ʿ���û�иô�
		if (s_temp1.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[1]=1;
			Keywords[i].libnum[0]=0;
			LIB[1]++;
		}
		else
			Keywords[i].libnum[1]=0;
		if (s_temp2.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[2]=1;
			Keywords[i].libnum[0]=0;
			LIB[2]++;
		}
		else
			Keywords[i].libnum[2]=0;
		//if (s_temp3.find(Keywords[i].s)!=string::npos)
		//{
			//Keywords[i].libnum[3]=1;
			//Keywords[i].libnum[0]=0;
			//LIB[3]++;
		//}
		//else
			//Keywords[i].libnum[3]=0;
	}
	for(i=0;i<=2;i++)
		cout<<LIB[i]<<"  ";
	for(i=0;i<=keyword_num-1;i++)
	{
		if(Keywords[i].libnum[0]==1)
			cout<<Keywords[i].s<<":�ʿ����޸ôʣ�";
		else
		{
			cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<"  :���ڴʿ�";
			for(j=0;j<=2;j++)
				if(Keywords[i].libnum[j]==1)
					cout<<j;
		}
		cout<<endl;
	}
}

void KW_Emo_Level_Classify()
{
	int i=0,j=0;
	string s_temp1,s_temp2,s_temp3,s_temp4,s_temp5,s_temp6;

	ifstream fin1("1.����.txt");
	ifstream fin2("2.��.txt");
	ifstream fin3("3.�Ƚ�.txt");
	ifstream fin4("4.��΢.txt");
	ifstream fin5("5.Ƿ.txt");
	ifstream fin6("6.����.txt");
	
	fin1>>s_temp1;fin1.close();fin1.clear();
	fin2>>s_temp2;fin2.close();fin2.clear();
	fin3>>s_temp3;fin3.close();fin3.clear();
	fin4>>s_temp4;fin4.close();fin4.clear();
	fin5>>s_temp5;fin5.close();fin5.clear();
	fin6>>s_temp6;fin6.close();fin6.clear();

	cout<<"������г̶ȴʿ���������£�"<<endl;
    LIB[1]=LIB[2]=LIB[3]=LIB[4]=LIB[5]=LIB[6]=0;
	
	for(i=0;i<=keyword_num-1;i++)
	{
		//Keywords[i].s="��"+Keywords[i].s+"��";
		Keywords[i].libnum[0]=1;//�ʿ���û�иô�
		if (s_temp1.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[1]=1;
			Keywords[i].libnum[0]=0;
			LIB[1]++;
			//cout<<endl<<s_temp1.find(Keywords[i].s)<<endl;
			//cout<<Keywords[i].s<<"��1���ҵ���";
		}
		else
			Keywords[i].libnum[1]=0;
		if (s_temp2.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[2]=1;
			Keywords[i].libnum[0]=0;
			LIB[2]++;
		}
		else
			Keywords[i].libnum[2]=0;
		if (s_temp3.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[3]=1;
			Keywords[i].libnum[0]=0;
			LIB[3]++;
		}
		else
			Keywords[i].libnum[3]=0;
		//cout<<endl<<s_temp3.find(Keywords[i].s)<<endl;
		if (s_temp4.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[4]=1;
			Keywords[i].libnum[0]=0;
			//cout<<endl<<s_temp4.find(Keywords[i].s)<<endl;
			LIB[4]++;
		}
		else
			Keywords[i].libnum[4]=0;
		if (s_temp5.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[5]=1;
			Keywords[i].libnum[0]=0;
			LIB[5]++;
		}
		else
			Keywords[i].libnum[5]=0;
		if (s_temp6.find(Keywords[i].s)!=string::npos)
		{
			Keywords[i].libnum[6]=1;
			Keywords[i].libnum[0]=0;
			LIB[6]++;
		}
		else
			Keywords[i].libnum[6]=0;
	}
	for(i=0;i<=6;i++)
		cout<<LIB[i]<<"  ";
	for(i=0;i<=keyword_num-1;i++)
	{
		if(Keywords[i].libnum[0]==1)
			cout<<Keywords[i].s<<":�ʿ����޸ôʣ�";
		else
		{
			cout<<Keywords[i].s<<":"<<Keywords[i].keyword_freq<<"  :���ڴʿ�";
			for(j=0;j<=6;j++)
				if(Keywords[i].libnum[j]==1)
					cout<<j;
		}
		cout<<endl;
	}
}

/*******
void SplitGBK(char *sInput)
{//�ִ���ʾ

	//��ʼ���ִ����
	if(!NLPIR_Init("..",0))//�����ڵ�ǰ·���£�Ĭ��ΪGBK����ķִ�
	{
		printf("ICTCLAS INIT FAILED!~~~\n");
		return ;
	}

	ICTCLAS_SetPOSmap(ICT_POS_MAP_SECOND);

	//char sSentence[5000]="ICTCLAS�ڹ���973ר������֯�������л����˵�һ�����ڵ�һ��������Ĵ����о�����SigHan��֯�������ж�����˶����һ����";
	const char * sResult;


	int nCount;
	ICTCLAS_ParagraphProcessA(sInput,&nCount);
	printf("nCount=%d\n",nCount);
	nCount = ICTCLAS_GetParagraphProcessAWordCount(sInput);
	const result_t *pResult=ICTCLAS_ParagraphProcessA(sInput,&nCount);

	int i=1;
	char *sWhichDic;
	for(i=0;i<nCount;i++)
	{
		sWhichDic="";
		switch (pResult[i].word_type)
		{
		case 0:
			sWhichDic = "���Ĵʵ�";
			break;
		case 1:
			sWhichDic = "�û��ʵ�";
			break;
		case 2:
			sWhichDic = "רҵ�ʵ�";
			break;
		default:
			break;
		}
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, sWhichDic,sInput+pResult[i].start );
	}
	while(_stricmp(sInput,"q")!=0)
	{
		sResult = ICTCLAS_ParagraphProcess(sInput,1);
		printf("%s\nInput string now('q' to quit)!\n", sResult);// 
		gets(sInput);
	}
	
	//�����û��ʵ�ǰ
	printf("δ�����û��ʵ䣺\n");
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//�����û��ʵ��
	printf("\n�����û��ʵ��\n");
	nCount = ICTCLAS_ImportUserDict("userdic.txt");//userdic.txt������ǰ���û��ʵ�
	//�����û��ʵ�
	ICTCLAS_SaveTheUsrDic();
	printf("����%d���û��ʡ�\n", nCount);
	
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//��̬����û���
	printf("\n��̬����û��ʺ�\n");
	ICTCLAS_AddUserWord("�����ѧԺ   xueyuan");
	ICTCLAS_SaveTheUsrDic();
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);


	//���ļ����зִ�
	//ICTCLAS_FileProcess("test2.txt","test2_result.txt",1);
	//ICTCLAS_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//�ͷŷִ������Դ
	ICTCLAS_Exit();
}

/*************************************************
void SplitGBK_Fanti(const char *sInput)
{//�ִ���ʾ

	//��ʼ���ִ����
	if(!ICTCLAS_Init("",GBK_FANTI_CODE))//�����ڵ�ǰ·���£�Ĭ��ΪGBK����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

	ICTCLAS_SetPOSmap(ICT_POS_MAP_SECOND);

	char sSentence[5000]="ICTCLAS�ڹ���ר������֯�������л����˵�һ�����ڵ�һ��������Ĵ����о�����SigHan��֯�������ж�����˶����һ����ICTCLAS�ڇ��Ȍ��ҽM�M�����u�y�л�ӫ@���˵�һ�����ڵ�һ�Ç��H����̎���о��C��SigHan�M�����u�y�ж��@���˶�헵�һ����";
	const char * sResult;


	int nCount;
	ICTCLAS_ParagraphProcessA(sSentence,&nCount);
	printf("nCount=%d\n",nCount);
	int count = ICTCLAS_GetParagraphProcessAWordCount(sSentence);
	const result_t *pResult=ICTCLAS_ParagraphProcessA(sSentence,&nCount);

	int i=1;
	char *sWhichDic;
	for(i=0;i<nCount;i++)
	{
		sWhichDic="";
		switch (pResult[i].word_type)
		{
		case 0:
			sWhichDic = "���Ĵʵ�";
			break;
		case 1:
			sWhichDic = "�û��ʵ�";
			break;
		case 2:
			sWhichDic = "רҵ�ʵ�";
			break;
		default:
			break;
		}
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, sWhichDic,sSentence+pResult[i].start );
	}
	while(_stricmp(sSentence,"q")!=0)
	{
		sResult = ICTCLAS_ParagraphProcess(sSentence,0);
		printf("%s\nInput string now('q' to quit)!\n", sResult);// 
		scanf("%s",sSentence);
	}
	
	//�����û��ʵ�ǰ
	printf("δ�����û��ʵ䣺\n");
	sResult = ICTCLAS_ParagraphProcess(sInput, 0);
	printf("%s\n", sResult);

	//�����û��ʵ��
	printf("\n�����û��ʵ��\n");
	nCount = ICTCLAS_ImportUserDict("userdic.txt");//userdic.txt������ǰ���û��ʵ�
	//�����û��ʵ�
	ICTCLAS_SaveTheUsrDic();
	printf("����%d���û��ʡ�\n", nCount);
	
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//��̬����û���
	printf("\n��̬����û��ʺ�\n");
	ICTCLAS_AddUserWord("�����ѧԺ   xueyuan");
	ICTCLAS_SaveTheUsrDic();
	sResult = ICTCLAS_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);


	//���ļ����зִ�
	ICTCLAS_FileProcess("test2.txt","test2_result.txt",1);
	ICTCLAS_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//�ͷŷִ������Դ
	ICTCLAS_Exit();
}
void SplitBIG5()
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init("",BIG5_CODE))//�����ڵ�ǰ·���£�����ΪBIG5����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testBIG.txt","testBIG_result.txt");
	ICTCLAS_Exit();
}
void SplitUTF8()
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init("",UTF8_CODE))//�����ڵ�ǰ·���£�����ΪUTF8����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("testUTF.txt","testUTF_result.txt");
	//ICTCLAS_FileProcess("test.xml","testUTF_result.xml");


	FILE *fp=fopen("TestUTF8-bigfile.txt","rt");
	if (fp==NULL)
	{
		printf("Error Open TestUTF8-bigfile.txt\n");
		ICTCLAS_Exit();
		return ;
	}
	char sLine[10241];
	int i,nCount,nDocID=1;
	//result_t res[1000];
	//while (fgets(sLine,10240,fp))
	{
		CICTCLAS *pICTCLAS=new CICTCLAS;
	/*	
		int nCountA=pICTCLAS->GetParagraphProcessAWordCount(sLine);
		pICTCLAS->ParagraphProcessAW(nCountA,res);
		for(i=0;i<nCountA;i++)
		{
			printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d\n",
				i+1, res[i].start, res[i].length, res[i].iPOS, res[i].word_ID);
		}

	
		fseek(fp,0,SEEK_END);
		int nSize=ftell(fp);

		fseek(fp,0,SEEK_SET);
		fread(sLine,nSize,1,fp);
		sLine[nSize]=0;
		const result_t *pResult=pICTCLAS->ParagraphProcessA(sLine,&nCount);
	    i=1;

		for(i=0;i<500&&i<nCount;i++)
		{
 			printf("\nNo.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d\n",
 				i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID);
			fwrite(sLine+pResult[i].start,sizeof(char),pResult[i].length,stdout);
		}
		delete pICTCLAS;
		printf("Processed docs %d\r",nDocID++);
	}

	ICTCLAS_Exit();
}

void testMultiThread()
{
	//��ʼ���ִ����
	if(!ICTCLAS_Init("",UTF8_CODE))//�����ڵ�ǰ·���£�����ΪUTF8����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	ICTCLAS_FileProcess("E:\\ictclas2010\\����\\�п�Ժ�ִʳ�����\\long_utf8.txt","E:\\ictclas2010\\����\\�п�Ժ�ִʳ�����\\long_utf8_result.txt");
	ICTCLAS_FileProcess("E:\\ictclas2010\\����\\�п�Ժ�ִʳ�����\\long.txt","E:\\ictclas2010\\����\\�п�Ժ�ִʳ�����\\long_result.txt");	
	ICTCLAS_Exit();
}*****************/
int main()
{
	int cl;
	testWord(GBK_CODE);
	KW_Topic_Classify();
	int ccount_topic[10]={517,460,461,542,550,489,517,331,496,452};
	cl=NaiveBayes(10,ccount_topic,4815);
	switch(cl)
	{
		case 1:cout<<"�������������࣡"<<endl;break;
		case 2:cout<<"��������ҽ�Ʊ����࣡"<<endl;break;
		case 3:cout<<"�������������࣡"<<endl;break;
		case 4:cout<<"�������������࣡"<<endl;break;
		case 5:cout<<"�������������࣡"<<endl;break;
		case 6:cout<<"�������������࣡"<<endl;break;
		case 7:cout<<"�������ڿƼ��࣡"<<endl;break;
		case 8:cout<<"�������ھ����࣡"<<endl;break;
		case 9:cout<<"�������ڲƾ��࣡"<<endl;break;
		case 10:cout<<"�������ڽ����Ļ��࣡"<<endl;break;
		default:cout<<"�޷�ʶ��"<<endl;
	}
	
   KW_Emo_Classify();
	int ccount_emo[2]={3922,3866};//,4727};
	//int ccount_emo[5]={2786,1134,3168,697,4727};
	cl=NaiveBayes(2,ccount_emo,7788);
	switch(cl)
	{
		case 1:cout<<"�������ڸ�������࣡"<<endl;break;
		case 2:cout<<"����������������࣡"<<endl;break;
		case 3:cout<<"����������������࣡"<<endl;break;
		default:cout<<"�޷�ʶ��"<<endl;
	}
	//KW_Emo_Level_Classify();
	/*int ccount_level[6]={69,42,35,29,12,30};
	cl=NaiveBayes(6,ccount_level,217);
	switch(cl)
	{
		case 1:cout<<"��г̶����ڡ����䡱����"<<endl;break;
		case 2:cout<<"��г̶����ڡ��ܡ�����"<<endl;break;
		case 3:cout<<"��г̶����ڡ��Ƚϡ�����"<<endl;break;
		case 4:cout<<"��г̶����ڡ���΢������"<<endl;break;
		case 5:cout<<"��г̶����ڡ�Ƿ������"<<endl;break;
		case 6:cout<<"��г̶����ڡ����ȡ�����"<<endl;break;
		default:cout<<"�޷�ʶ��"<<endl;
	}*/
	system("pause");
	return 1;
}

