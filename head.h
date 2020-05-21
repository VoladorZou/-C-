#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ö���͸�λ������Ա������Ա�����۾�������
enum workpost { SALESMAN = 0, TECHNICIAN, SALESMANAGER, MANAGER };
//Ա�����ͣ�������
struct Employee {
	int  id;				//Ա���ţ�������Ψһ
	char name[10];			//����
	char sex[3];			//�Ա��л�Ů
	int  age;				//����
	char department[20];	//����
	enum workpost post;		//ö���͸�λ
	int  workHour;			//���¹���Сʱ��
	double sales;			//���������۶�
	double salary;			//�¹���
	struct Employee * next;//�����ָ����
};
#define LENGTH 50
//ȫ�ֱ���
Employee Employees[LENGTH];
typedef int DataType;
Employee *head;
int select = 1;//����ѡ�����
int subselect = 1;//�ӹ���ѡ�����
FILE *fp;
int i = 0;//ѭ������
//��������
void ListInitiate(Employee **head);
void Load();
void Check();
void AddData();
void UpdataData();
void QueryData();
void DeleteData();
void Sorting();
void Statistics();
void Save();
//�˵�����
  //Ҫ������������˵���
void Menu()
{
	while (select)
	{
		printf("����������������Ա�����ʹ���ϵͳ����������������\n");
		printf("��������1. ��������           2. �޸����ݡ�������\n");
		printf("��������3. ��������           4. ɾ�����ݡ�������\n");
		printf("��������5. ������           6. ͳ�����ݡ�������\n");
		printf("��������0. �˳�����           7. �鿴����������\n");
		printf("���������ѡ��\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			AddData();
			break;
		case 2:
			UpdataData();
			break;
		case 3:
			QueryData();
			break;
		case 4:
			DeleteData();
			break;
		case 5:
			Sorting();
			break;
		case 6:
			Statistics();
			break;
		case 7:
			Check();
			break;
		case 0: break;
		default: printf("�������������ѡ��\n");
		}
	}
}
//���ܺ���
  //��ʼ��������
void ListInitiate(Employee **head)//head��һ��ָ�룬*headҲ��һ��ָ��
{
	*head = (Employee *)malloc(sizeof(Employee));//����ͷ���
	(*head)->next = NULL;
}
//�������ļ����洢Ա����Ϣ��
	//��ʼ���г���ʱ���ļ��ж�ȡԱ����Ϣ�������˳�����ʱ��Ա����Ϣ���浽�ļ��С�
void Load() {
	if ((fp = fopen("Employee.txt", "ab+")) == NULL)
	{
		printf("���ļ�����\n");
		exit(1);
	}
	//δ֪�ļ����ȣ�ʹ��feof(FILE *Stream)�ж��ļ���β
	while (!feof(fp))
	{
		//feof(fp)ͨ��fread/fscanf�Ƿ��д�����жϣ�Ӧ���ڶ�д����֮������жϣ���������һ��ѭ��
		if (fread(&Employees[i], sizeof(struct Employee), 1, fp) == 0)
		{
			continue;
		}
		Employee *p, *q;//�ֱ�����ָ���i�����ʹ�������½��
		p = head;
		while (p->next != NULL)//��ָ��P��λ������βλ��
		{
			p = p->next;
		}
		q = (Employee *)malloc(sizeof(Employee));//��ָ��Q�����½��
		//�������ݵ�������
		q->id = i;
		q->id++;
		strcpy(q->name, Employees[i].name);
		strcpy(q->sex, Employees[i].sex);
		q->age = Employees[i].age;
		strcpy(q->department, Employees[i].department);
		q->post = Employees[i].post;
		q->workHour = Employees[i].workHour;
		q->sales = Employees[i].sales;//���������۶�
		q->salary = Employees[i].salary;//�¹���
		q->next = p->next;//Qָ���next��ָ��Pָ���next�򣬼���i�����
		p->next = q;
		i++;
	}
	fclose(fp);
}
//����������������Ƿ�׼ȷ
void Check()
{
	Employee *p;
	p = head;
	if (p->next == NULL)
	{
		printf("����Ϊ�գ�\n");
	}
	else
	{
		printf("������������Ϊ��\n");
		while (p->next != NULL)
		{
			p = p->next;
			printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
		}
		printf("�����ϣ�\n");
	}
}
//��������
  //���һ��Ա����ֻ�����Ա���Ļ�����Ϣ�����������䡢�Ա𡢲��š���λ����
void AddData()
{
	Employee *p, *q;//�ֱ�����ָ���i�����ʹ�������½��
	p = head;
	while (p->next != NULL)//��ָ��P��λ������βλ��
	{
		p = p->next;
	}
	q = (Employee *)malloc(sizeof(Employee));//��ָ��Q�����½��
	i++;
	q->id = i;
	printf("������Ա��������\n");
	scanf("%s", q->name);
	printf("������Ա�����䣺\n");
	scanf("%d", &q->age);
	printf("������Ա���Ա�\n");
	scanf("%s", q->sex);
	printf("������Ա�����ţ�\n");
	scanf("%s", q->department);
	printf("������Ա����λ��\n");
	scanf("%d", &q->post);
	q->workHour = 0;
	if (q->post == 3)
	{
		q->salary = 8000.0;
	}
	else
	{
		q->salary = 0.0;
	}
	q->sales = 0.0;
	q->next = p->next;//Qָ���next��ָ��Pָ���next�򣬼���i�����
	p->next = q;
	printf("��ӳɹ���\n");
}
//�޸�����
/*
1)����Ա�������޸�����Ա���Ļ�����Ϣ�����������䡢�Ա𡢲��š���λ����
2)�����������м���Ա�ĵ��¹��ʶ����д����Ա���¹���ʱ�䣩��
3)����������������Ա�ĵ��¹��ʶ����д����Ա�������۶��Ȼ�����������������۾���ĵ��¹��ʶ
*/
void UpdataData()
{
	subselect = 1;
	Employee *p, *p1;
	p = head;
	while (subselect)
	{
		printf("������������  �޸����ݵĶ����˵�  ������������\n");
		printf("����1. ����Ա�������޸�����Ա���Ļ�����Ϣ\n");
		printf("����2. �����������м���Ա�ĵ��¹��ʶ�\n");
		printf("����3. ����������������Ա�ĵ��¹��ʶȻ�����������������۾���ĵ��¹��ʶ�\n");
		printf("����0. �˳����Ӳ˵�\n");
		printf("���������ѡ��\n");
		scanf("%d", &subselect);
		switch (subselect)
		{
		case 1:
			p = head;
			int ID;
			printf("��������޸ĵ�Ա����Ϣ��Ա���ţ�\n");
			scanf("%d", &ID);
			while (p->next != NULL)
			{
				p = p->next;
				if (p->id == ID)
				{
					printf("�������µ�Ա��������\n");
					scanf("%s", p->name);
					printf("�������µ�Ա�����䣺\n");
					scanf("%d", &p->age);
					printf("�������µ�Ա���Ա�\n");
					scanf("%s", p->sex);
					printf("�������µ�Ա�����ţ�\n");
					scanf("%s", p->department);
					printf("�������µ�Ա����λ��\n");
					scanf("%d", &p->post);
					printf("��Ϣ¼��ɹ���\n");
					break;
				}
			}
			break;
		case 2:
			//�����������м���Ա�ĵ��¹��ʶ����Ա���ʣ�����ʱ�䣪Сʱ���ʣ�100ԪÿСʱ��
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post == 1)
				{
					printf("����дԱ����Ϊ%d�ļ���Ա���¹���ʱ�䣺\n", p->id);
					scanf("%d", &p->workHour);
					p->salary = p->workHour * 100;
				}
			}
			break;
		case 3:
			//����Ա���ʣ����۶4%��ɣ�
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post == 0)
				{
					printf("����дԱ����Ϊ%d������Ա�������۶\n", p->id);
					scanf("%lf", &p->sales);
					p->salary = p->sales*0.04;
				}
			} 
			//���۾�����н��5000������Ͻ�������۶��ܶ0.5%��
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				p1 = head;
				double sum_of_sales = 0.0;
				if (p->post == 2)
				{
				while(p1->next != NULL)
				{
					p1 = p1->next;
				    if (strcmp(p->department, p1->department)==0)
				    {
					   sum_of_sales += p1->sales ;
				    }
				}
				p->salary = sum_of_sales * 0.005 + 5000;
				}
			}
			break;
		case 0:
			break;
		default:
			printf("�������������ѡ��\n");
		}
	}
}
//��ѯ����
void QueryData()
{
	subselect = 1;
	Employee *p;
	p = head;
	while (subselect)
	{
		printf("������������  ��ѯ���ݵĶ����˵�   ������������\n");
		printf("����1. ���ݹ��Ż���������ѯԱ����Ϣ\n");
		printf("����2. ��������ʾ������ȫ��Ա����Ϣ\n");
		printf("����3. �ֱ���ʾ4�ָ�λ��Ա����Ϣ\n");
		printf("����4. ��ҳ��ʾȫ��Ա������Ϣ\n");
		printf("����0. �˳����Ӳ˵�\n");
		printf("���������ѡ��\n");
		scanf("%d", &subselect);
		switch (subselect)
		{
		case 1:
			p = head;
			int ID;
			printf("�����빤�ţ�\n");
			scanf("%d", &ID);
			while (p->next != NULL)
			{
				p = p->next;
				if (p->id == ID)
			{
			printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
		    printf("�����ϣ�\n");
	        }
	        }
		break;
		case 2:
			char Department[20];
			printf("�����벿�����ƣ�\n");
					scanf("%s", &Department);
			p = head;
			while(p->next != NULL)
				{
					p = p->next;
				    if (strcmp(p->department, Department)==0)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
				}
				printf("�����ϣ�\n");
			
		break;
		case 3:
			printf("SALESMAN:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==0)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("TECHNICIAN:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==1)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("SALESMANAGER:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==2)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("MANAGER:\n");
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
				if (p->post==3)
				    {
					   printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				    }
			} 
			printf("�����ϣ�\n");
		break;
		case 4:
			printf("��ҳ�������ѣ�ûѧ��������ʱ���հ�\n");
		break;
		case 0:
		break;
		default:
		printf("�������������ѡ��\n");
		}
    }
	
}
//ɾ������
void DeleteData(){
	Employee *p, *s;
	p = head;
	printf("������Ҫɾ��Ա����Ϣ��Ա���ţ�\n");
	scanf("%d", &i);
	while (p->next != NULL)
	{
		s = p;
		p = p->next;
		if(p->id==i) break;	
	}
	s->next = s->next->next;
	free(p);
}

//��Ҫ������
void Sorting()
{
	subselect = 1;
	Employee *p, *p1;
	int z = 0;
	int f=0;
	int count = 0;
	double s[20];
	double storeNum;
	p = head;
	while (subselect)
	{
		printf("������������  �������ݵĶ����˵�   ������������\n");
		printf("����1. ����Ա����Ϣ�����¹��ʴӸߵ��Ͳ���ʾ\n");
		printf("����2. ĳ����λ��Ա����Ϣ�����¹��ʴӸߵ�����ʾ\n");
		printf("����0. �˳����Ӳ˵�\n");
		printf("���������ѡ��\n");
		scanf("%d", &subselect);
		switch (subselect)
		{
		case 1:
			p = head;
			z = 0; 
			while (p->next != NULL)
			{
				p = p->next;
				s[z] = p->salary;
				z++;
			}
			//ð������ 
			for (int i = 0; i < z-1; i++)//��Ϊ���������Ƚϣ�10��������������Ҫ����9��
	        {
		    for (int j = 0; j < (z-1) - i; j++)//��Ϊÿ����һ�˾Ϳ����ź�һ����������ѭ������-i
		    {
			if (s[j] > s[j+1])//�����Ƚ�
			{
				double temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		    }
	        }
	        z--;
			for (int i = z; i >= 0; i--)
			{
				if(storeNum == s[i])
				{
					continue;
				}
			    p = head;
			    while (p->next != NULL)
			    {
				p = p->next;
			    storeNum = s[i];
				if(p->salary==s[i])
				{
					printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				}
			}
		}
		break;	
		case 2:
			int Post;
			z = 0;
			storeNum = 0.0;
			printf("�������λ��Ϣ����SALESMAN = 0, TECHNICIAN, SALESMANAGER, MANAGER��\n");
			scanf("%d", &Post);
			p = head;
			while(p->next != NULL)
				{
					p = p->next;
				    if (p->post==Post)
				    {
				    	s[z] = p->salary;
				        z++;
			       }
	        	}
			//ð������ 
			for (int i = 0; i < z-1; i++)
	        {
		    for (int j = 0; j < (z-1) - i; j++)//��Ϊÿ����һ�˾Ϳ����ź�һ����������ѭ������-i
		    {
			if (s[j] > s[j+1])//�����Ƚ�
			{
				double temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		    }
	        }
	        z--;
	        for (int i = z; i >= 0; i--)
			{
				if(storeNum == s[i])
				{
					continue;
				}
			    p = head;
			    while (p->next != NULL)
			    {
				p = p->next;
				if(p->salary==s[i]&&p->post==Post)
				{
					storeNum = s[i];
					printf("%d %s %s %d %s ", p->id, p->name, p->sex, p->age, p->department);
			switch (p->post)
			{
			case 0:
				printf("SALESMAN    ");
				break;
			case 1:
				printf("TECHNICIAN  ");
				break;
			case 2:
				printf("SALESMANAGER");
				break;
			case 3:
				printf("MANAGER     ");
				break;
			default:
				printf("��������\n");
				break;
			}
			printf(" %d  %.2lf  %.2lf\n", p->workHour, p->sales, p->salary);
				}
			}
	     	}		    	
		break;
		case 0:
		break;
		default:
		printf("�������������ѡ��\n");
	}
    }	
}
//ͳ������
void Statistics()
{
	printf("hh\n");
}
//�����������ݵ��ļ�
void Save()
{
	Employee *p;
	p = head;
	i = 0;
	//��һ���������еĽ����Ϣ����������
	while (p->next != NULL)
	{
		p = p->next;
		Employees[i].id = p->id;
		strcpy(Employees[i].name, p->name);
		strcpy(Employees[i].sex, p->sex);
		Employees[i].age = p->age;
		strcpy(Employees[i].department, p->department);
		Employees[i].post = p->post;
		Employees[i].workHour = p->workHour;
		Employees[i].sales = p->sales;//���������۶�
		Employees[i].salary = p->salary;//�¹���
		i++;
	}
	//�ڶ�������������¼���ı��ļ�
	if ((fp = fopen("employee.txt", "wb+")) == NULL)
	{
		printf("���ļ�����\n");
		exit(1);
	}
	p = head;
	i = 0;
	while (p->next != NULL)
	{
		p = p->next;
		if (fwrite(&Employees[i], sizeof(struct Employee), 1, fp) != 1)
		{
			printf("д���ļ�����\n");
		}
		i++;
	}
	fclose(fp);
	printf("�ɹ��������ݵ��ı��ļ�employee\n");
}
