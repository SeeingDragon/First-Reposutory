#include<iostream>
#include<string>
using namespace std;
#define max 1000
//菜单界面
void showMenu() {
    cout << "1、添加联系人" << endl;
    cout << "2、显示联系人" << endl;
    cout << "3、删除联系人" << endl;
    cout << "4、查找联系人" << endl;
    cout << "5、修改联系人" << endl;
    cout << "6、清空联系人" << endl;
    cout << "0、推出通讯录" << endl;
}
struct person//联系人结构
{
    string name;//姓名
    string sex;//性别
    int age;//年龄
    string phone;//电话号码
    string address;//地址
};
struct Address_Book//通讯录结构
{
    struct person personArray[max];//通过通讯录保存联系人数组
    int size;
};
void addperson(Address_Book* abs) {
    string name;//姓名
    string sex;//性别
    int age;//年龄
    string phone;//电话号码
    string address;//地址
    cout << "请输入联系人姓名" << endl;
    cin >> name;
    abs->personArray[abs->size].name = name;
    cout << "请输入联系人性别" << endl;
    cin >> sex;
    abs->personArray[abs->size].sex = sex;
    cout << "请输入联系人年龄" << endl;
    cin >> age;
    if (cin.fail())
    {
        cout << "输入错误";
        exit(0);
    }
    else {
        abs->personArray[abs->size].age = age;
    }

    cout << "请输入联系人电话" << endl;
    cin >> phone;
    abs->personArray[abs->size].phone = phone;
    cout << "请输入联系人地址" << endl;
    cin >> address;
    abs->personArray[abs->size].address = address;
    abs->size++;

}
void showperson(Address_Book* abs) {
    if (abs->size == 0)
    {
        cout << "通讯录为空" << endl;
    }
    else {
        for (int i = 0; i < abs->size; i++)
        {
            cout << "姓名:" << abs->personArray[i].name << "  ";
            cout << "性别:" << abs->personArray[i].sex << "  ";
            cout << "年龄:" << abs->personArray[i].age << "  ";
            cout << "电话:" << abs->personArray[i].phone << "  ";
            cout << "地址:" << abs->personArray[i].address << "  ";
            cout << endl;
        }
    }

}
int isexist(Address_Book* abs, string name) {//查看该联系人是否存在
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
    cout << "请输入要删除的联系人姓名" << endl;
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
    else cout << "查无此人" << endl;
}
void findperson(Address_Book* abs) {
    string name;
    cout << "请输入要查找的联系人姓名" << endl;
    cin >> name;
    int ret = isexist(abs, name);
    if (ret != -1)
    {
        cout << "姓名:" << abs->personArray[ret].name << "  ";
        cout << "性别:" << abs->personArray[ret].sex << "  ";
        cout << "年龄:" << abs->personArray[ret].age << "  ";
        cout << "电话:" << abs->personArray[ret].phone << "  ";
        cout << "地址:" << abs->personArray[ret].address << "  ";
        cout << endl;
    }
    else cout << "查无此人" << endl;
}
void recompose(Address_Book* abs) {
    string name;
    string s;
    string ss;
    int age;
    cout << "请输入要修改的的联系人姓名" << endl;
    cin >> name;
    int ret = isexist(abs, name);
    if (ret != -1) {
        cout << "请输入要修改的值（如姓名、电话）";
        cin >> s;
        if (s == "姓名") {
            cout << "请输入要修改的姓名" << endl;
            cin >> ss;
            abs->personArray[ret].name = ss;
        }
        else if (s == "性别") {
            cout << "请输入要修改的性别" << endl;
            cin >> ss;
            abs->personArray[ret].sex = ss;
        }
        else if (s == "年龄") {
            cout << "请输入要修改的年龄" << endl;
            cin >> age;
            abs->personArray[ret].age = age;
        }
        else if (s == "电话") {
            cout << "请输入要修改的电话" << endl;
            cin >> ss;
            abs->personArray[ret].phone = ss;
        }
        else if (s == "地址") {
            cout << "请输入要修改的地址" << endl;
            cin >> ss;
            abs->personArray[ret].address = ss;
        }
        else {
            cout << "输入错误" << endl;
            exit(0);
        }

    }

}
void empty_person(Address_Book* abs) {//逻辑清空
    if (abs->size == 0) cout << "通讯录为空" << endl;
    abs->size = 0;
    cout << "操作成功,通讯录已清空";
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
        cout << "请选择要进行的操作";
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
            cout << "退出成功" << endl;
            return 0;
            break;
        default:
            cout << "输入错误，程序自动退出" << endl;
            return 0;
            break;
        }
    }
    system("pause");
    return 0;
}