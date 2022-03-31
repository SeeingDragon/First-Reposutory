#include<iostream>
#include<string>
using namespace std;
#define max 1000
//�˵�����
void showMenu() {
    cout << "1�������ϵ��" << endl;
    cout << "2����ʾ��ϵ��" << endl;
    cout << "3��ɾ����ϵ��" << endl;
    cout << "4��������ϵ��" << endl;
    cout << "5���޸���ϵ��" << endl;
    cout << "6�������ϵ��" << endl;
    cout << "0���Ƴ�ͨѶ¼" << endl;
}
struct person//��ϵ�˽ṹ
{
    string name;//����
    string sex;//�Ա�
    int age;//����
    string phone;//�绰����
    string address;//��ַ
};
struct Address_Book//ͨѶ¼�ṹ
{
    struct person personArray[max];//ͨ��ͨѶ¼������ϵ������
    int size;
};
void addperson(Address_Book* abs) {
    string name;//����
    string sex;//�Ա�
    int age;//����
    string phone;//�绰����
    string address;//��ַ
    cout << "��������ϵ������" << endl;
    cin >> name;
    abs->personArray[abs->size].name = name;
    cout << "��������ϵ���Ա�" << endl;
    cin >> sex;
    abs->personArray[abs->size].sex = sex;
    cout << "��������ϵ������" << endl;
    cin >> age;
    if (cin.fail())
    {
        cout << "�������";
        exit(0);
    }
    else {
        abs->personArray[abs->size].age = age;
    }

    cout << "��������ϵ�˵绰" << endl;
    cin >> phone;
    abs->personArray[abs->size].phone = phone;
    cout << "��������ϵ�˵�ַ" << endl;
    cin >> address;
    abs->personArray[abs->size].address = address;
    abs->size++;

}
void showperson(Address_Book* abs) {
    if (abs->size == 0)
    {
        cout << "ͨѶ¼Ϊ��" << endl;
    }
    else {
        for (int i = 0; i < abs->size; i++)
        {
            cout << "����:" << abs->personArray[i].name << "  ";
            cout << "�Ա�:" << abs->personArray[i].sex << "  ";
            cout << "����:" << abs->personArray[i].age << "  ";
            cout << "�绰:" << abs->personArray[i].phone << "  ";
            cout << "��ַ:" << abs->personArray[i].address << "  ";
            cout << endl;
        }
    }

}
int isexist(Address_Book* abs, string name) {//�鿴����ϵ���Ƿ����
    for (int i = 0; i < abs->size; i++)
    {
        if (abs->personArray[i].name == name)
        {
            return i;
        }
        else return -1;
    }
}
void deletperson(Address_Book* abs) {
    string name;
    cout << "������Ҫɾ������ϵ������" << endl;
    cin >> name;
    int ret = isexist(abs, name);
    if (ret != -1)
    {
        for (int i = ret; i < abs->size; i++)
        {
            abs->personArray[i] = abs->personArray[i + 1];
        }
        abs->size--;
    }
    else cout << "���޴���" << endl;
}
void findperson(Address_Book* abs) {
    string name;
    cout << "������Ҫ���ҵ���ϵ������" << endl;
    cin >> name;
    int ret = isexist(abs, name);
    if (ret != -1)
    {
        cout << "����:" << abs->personArray[ret].name << "  ";
        cout << "�Ա�:" << abs->personArray[ret].sex << "  ";
        cout << "����:" << abs->personArray[ret].age << "  ";
        cout << "�绰:" << abs->personArray[ret].phone << "  ";
        cout << "��ַ:" << abs->personArray[ret].address << "  ";
        cout << endl;
    }
    else cout << "���޴���" << endl;
}
void recompose(Address_Book* abs) {
    string name;
    string s;
    string ss;
    int age;
    cout << "������Ҫ�޸ĵĵ���ϵ������" << endl;
    cin >> name;
    int ret = isexist(abs, name);
    if (ret != -1) {
        cout << "������Ҫ�޸ĵ�ֵ�����������绰��";
        cin >> s;
        if (s == "����") {
            cout << "������Ҫ�޸ĵ�����" << endl;
            cin >> ss;
            abs->personArray[ret].name = ss;
        }
        else if (s == "�Ա�") {
            cout << "������Ҫ�޸ĵ��Ա�" << endl;
            cin >> ss;
            abs->personArray[ret].sex = ss;
        }
        else if (s == "����") {
            cout << "������Ҫ�޸ĵ�����" << endl;
            cin >> age;
            abs->personArray[ret].age = age;
        }
        else if (s == "�绰") {
            cout << "������Ҫ�޸ĵĵ绰" << endl;
            cin >> ss;
            abs->personArray[ret].phone = ss;
        }
        else if (s == "��ַ") {
            cout << "������Ҫ�޸ĵĵ�ַ" << endl;
            cin >> ss;
            abs->personArray[ret].address = ss;
        }
        else {
            cout << "�������" << endl;
            exit(0);
        }

    }

}
void empty_person(Address_Book* abs) {//�߼����
    if (abs->size == 0) cout << "ͨѶ¼Ϊ��" << endl;
    abs->size = 0;
    cout << "�����ɹ�,ͨѶ¼�����";
}
int  main() {
    showMenu();
    Address_Book abs;
    abs.size = 0;
    int select = 0;
    int flag = 1;
    while (true)
    {
        if (flag % 5 == 0) showMenu();
        cout << "��ѡ��Ҫ���еĲ���";
        cin >> select;
        switch (select)
        {
        case 1:
            flag++;
            addperson(&abs);
            break;
        case 2:
            flag++;
            showperson(&abs);
            break;
        case 3:
            flag++;
            deletperson(&abs);
            break;
        case 4:
            flag++;
            findperson(&abs);
            break;
        case 5:
            flag++;
            recompose(&abs);
            break;
        case 6:
            flag++;
            empty_person(&abs);
            break;
        case 0:
            cout << "�˳��ɹ�" << endl;
            return 0;
            break;
        default:
            cout << "������󣬳����Զ��˳�" << endl;
            return 0;
            break;
        }
    }
    system("pause");
    return 0;
}