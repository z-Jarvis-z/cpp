#include<cstdio>
//cin
//scanf
//getchar���
//fread�Ż��Ŀ��

//getchar �� scanf ��
//fread �� getchar ��

char buf[1 << 21], * p1 = buf, * p2 = buf;
//p1 is the start-pointer, p2 is the end-pointer
inline char gc()
{
	if (p1 == p2)
	{
		p2 = (p1 = buf ) + fread(buf, 1, 1 << 21, stdin);
	}
	return *(p1 ++);
}
inline int read()
{
	int s = 0, w = 1;//s��ָ��w����
	char ch = gc();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			w *= -1;
		ch = gc();
	}
	while (ch >= '0' && ch <= '9')
	{
		//s = s * 10 + ch - '0';
		s = (s << 1) + (s << 3) + (ch ^ 48);
		ch = gc();
	}
	return s * w;
}