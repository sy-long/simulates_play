#include <iostream>
#include <string>
#include<iomanip>

using namespace std;

#define CLR system("clear")
#define PAUSE cin.get();cin.get()

class Tower{
public:
    enum Damage_way{ORDINARY,LASER};
private:
    int id;
    int damage;
    int scope;
    Damage_way d_way;
public:
    Tower(int _id,int _damage,int _scope,Damage_way _d_way):id(_id),damage(_damage),scope(_scope),d_way(_d_way){}
    int get_damage(){return damage;}
    int get_scope(){return scope;}
    Damage_way get_d_way(){return d_way;}
    virtual string get_tower_type()=0;
    virtual ~Tower(){}
    friend ostream & operator<<(ostream &out, Tower &tower);
};

ostream & operator<<(ostream &out,Tower &tower){
    string type;
    if(tower.get_d_way()==Tower::ORDINARY) type="普通攻击";
    else type="激光攻击";
    out<<tower.id<<"   |"<<tower.get_damage()<<"   |"<<tower.get_scope()<<" |"<<type<<endl;
    return out;
}

class Ordinary_tower:public Tower{
public:
    Ordinary_tower():Tower(1,100,500,ORDINARY){}
    virtual string get_tower_type(){return "普通塔";}
    virtual ~Ordinary_tower(){}
};

class Highlands_tower:public Tower{
public:
    Highlands_tower():Tower(2,200,1000,LASER){}
    virtual string get_tower_type(){return "高地塔";}
    virtual ~Highlands_tower(){}
};

class Equipment{
public:
    enum Equipment_type{WEAPONS,ARMOR};
private:
    int value;
    Equipment_type e_type;
    int id;
public:
    Equipment(int _id,int _value,Equipment_type _e_type):id(_id),value(_value),e_type(_e_type){}
    int get_value(){return value;}
    Equipment_type get_e_type(){return e_type;}
    virtual string get_e_name()=0;
    virtual ~Equipment(){}
    friend ostream & operator<<(ostream &out,Equipment &equipment);
};
ostream & operator<<(ostream &out,Equipment &equipment){
    string type;
    if(equipment.e_type==Equipment::WEAPONS) type="武器";
    else type="防具";
    out<<equipment.id<<"   |   "<<equipment.value<<"    |"<<type<<endl;
    return out;
}

class B_F_Sword:public Equipment{
public:
    B_F_Sword():Equipment(1,40,WEAPONS){}
    virtual string get_e_name(){return "暴风之剑";}
    virtual ~B_F_Sword(){}
};

class Warmog_s_Armor:public Equipment{
public:
    Warmog_s_Armor():Equipment(2,50,ARMOR){}
    virtual string get_e_name(){return "狂徒铠甲";}
    virtual ~Warmog_s_Armor(){}
};

class Infinity_Edge:public Equipment{
public:
    Infinity_Edge():Equipment(3,80,WEAPONS){}
    virtual string get_e_name(){return "无尽之刃";}
    virtual ~Infinity_Edge(){}
};

class Thornmail:public Equipment{
public:
    Thornmail():Equipment(4,100,ARMOR){}
    virtual string get_e_name(){return "荆棘之甲";}
    virtual ~Thornmail(){}
};

class Role{
public:
    enum R_type{USER,NPC};
private:
    int id;
    int damage;
    int defense;
    int hp;
    R_type r_type;
    Equipment* equipment[6];
    int e_count;
public:
    Role(int _id,int _damage,int _defense,int _hp,R_type _r_type):id(_id),damage(_damage),defense(_defense),hp(_hp),
        r_type(_r_type),e_count(0){
        int i;
        for(i=0;i<6;i++) equipment[i]=NULL;
    }
    int get_damage(){return damage;}
    int get_defense(){return defense;}
    int get_hp(){return hp;}
    bool add_e(Equipment * target);
    R_type get_r_type(){return r_type;}
    virtual string get_r_name()=0;
    virtual ~Role(){
        int i;
        for(i=0;i<e_count;i++) delete equipment[i];
    }
    friend ostream & operator<<(ostream &out,Role &role);
};
ostream & operator<<(ostream &out,Role &role){
    string type;
    if(role.get_r_type()==Role::USER) type="英雄";
    else type="NPC";
    out<<role.id<<"   |"<<role.damage<<"    |"<<role.defense<<"    |"<<role.hp<<"   |"<<type<<endl;
    int i;
    if(role.e_count!=0)
        cout<<"名称"<<"    |"<<"编号"<<'|'<<"攻击/防御"<<'|'<<"类型"<<endl;
    for(i=0;i<role.e_count;i++){
        cout<<role.equipment[i]->get_e_name()<<"|";
        cout<<*(role.equipment[i]);
    }
    return out;
}
bool Role::add_e(Equipment * target){
    if(e_count>=6) return false;
    if(target->get_e_type()==Equipment::WEAPONS) damage+=target->get_value();
    else defense+=target->get_value();
    equipment[e_count]=target;
    e_count++;
    return true;
}

class Garen:public Role{
public:
    Garen():Role(1,80,50,600,USER){}
    virtual string get_r_name(){return "盖伦";}
    virtual ~Garen(){}
};

class Ashe:public Role{
public:
    Ashe():Role(2,95,40,500,USER){}
    virtual string get_r_name(){return "艾希";}
    virtual ~Ashe(){}
};

class Ryze:public Role{
public:
    Ryze():Role(3,90,45,550,USER){}
    virtual string get_r_name(){return "瑞兹";}
    virtual ~Ryze(){}
};

class Wolf:public Role{
public:
    Wolf():Role(4,20,20,300,NPC){}
    virtual string get_r_name(){return "三狼";}
    virtual ~Wolf(){}
};

class Bird:public Role{
public:
    Bird():Role(5,30,30,250,NPC){}
    virtual string get_r_name() {return "六鸟";}
    virtual ~Bird(){}
};

class Game{
private:
    Role* role[2];
    void new_line(int i);
    Tower *tower[2];
public:
    Game(){role[0]=NULL;role[1]=NULL;tower[0]=NULL;tower[1]=NULL;}
    bool welcome_face();
    void add_role();
    void Menu();
    void Show_role();
    void add_e();
    void add_tower();
    void run();
    ~Game();
};
Game::~Game(){
        if(role[0]!=NULL)
        delete role[0];
        if(role[1]!=NULL)
        delete role[1];
        if(tower[0]!=NULL)
            delete tower[0];
        if(tower[1]!=NULL)
            delete tower[1];
}
void Game::new_line(int line){
    int i;
    for(i=0;i<line;i++)
        cout<<"\n";
}
bool Game::welcome_face(){
    bool ret=false;
    int chiose;
    do{
        CLR;
        new_line(8);
        cout<<setw(55)<<"英雄联盟模拟器\n";
        new_line(2);
        cout<<setw(46)<<"1.进入系统\n";
        cout<<setw(46)<<"2.退出系统\n";
        new_line(2);
        cout<<setw(44)<<"请选择:";
        cin>>chiose;
        switch (chiose) {
            case 1:ret=true;break;
            case 2:ret=false;break;
            default:{
                CLR;
                new_line(8);
                cout<<setw(58)<<"选择错误，请重新选择！\n";
                PAUSE;
            }
        }
    }while(chiose!=1&&chiose!=2);
    return ret;
}
void Game::add_role(){
    CLR;
    cout<<"名字"<<'|'<<"编号"<<'|'<<"攻击力"<<'|'<<"防御力"<<'|'<<"生命值"<<'|'<<"类型"<<endl;
    Role *r;
    r=new Garen();
    cout<<r->get_r_name()<<'|';
    cout<<*r;
    delete r;
    r=new Ashe();
    cout<<r->get_r_name()<<'|';
    cout<<*r;
    delete r;
    r=new Ryze();
    cout<<r->get_r_name()<<'|';
    cout<<*r;
    delete r;
    r=new Wolf();
    cout<<r->get_r_name()<<'|';
    cout<<*r;
    delete r;
    r=new Bird();
    cout<<r->get_r_name()<<'|';
    cout<<*r;
    delete r;
    int state=0;
    while(state==0){
        cout<<"请选择角色一"<<endl;
        cout<<"请输入编号:";
        int chiose;
        cin>>chiose;
        switch(chiose){
        case 1:{role[0]=new Garen();state=1;}break;
        case 2:{role[0]=new Ashe();state=1;}break;
        case 3:{role[0]=new Ryze();state=1;}break;
        case 4:{role[0]=new Wolf();state=1;}break;
        case 5:{role[0]=new Bird();state=1;}break;
        default:{
            new_line(1);
            cout<<setw(58)<<"选择错误，请重新选择！\n";
            }
        }
    }
    state=0;
    while(state==0){
        cout<<"请选择角色二"<<endl;
        cout<<"请输入编号:";
        int chiose;
        cin>>chiose;
        switch(chiose){
        case 1:{role[1]=new Garen();state=1;}break;
        case 2:{role[1]=new Ashe();state=1;}break;
        case 3:{role[1]=new Ryze();state=1;}break;
        case 4:{role[1]=new Wolf();state=1;}break;
        case 5:{role[1]=new Bird();state=1;}break;
        default:{
            new_line(1);
            cout<<setw(58)<<"选择错误，请重新选择！\n";
            }
        }
    }
    new_line(1);
    cout<<"选择成功!";
    PAUSE;
}
void Game::Show_role(){
    CLR;
    cout<<"角色一:"<<endl;
    cout<<"名字"<<'|'<<"编号"<<'|'<<"攻击力"<<'|'<<"防御力"<<'|'<<"生命值"<<'|'<<"类型"<<endl;
    cout<<role[0]->get_r_name()<<'|';
    cout<<*(role[0]);
    if(tower[0]!=NULL){
        cout<<"类型"<<"  |"<<"编号"<<'|'<<"攻击力"<<'|'<<"范围"<<'|'<<"攻击类型"<<endl;
        cout<<tower[0]->get_tower_type()<<"|";
        cout<<*tower[0];
    }
    new_line(2);
    cout<<"角色二:"<<endl;
    cout<<"名字"<<'|'<<"编号"<<'|'<<"攻击力"<<'|'<<"防御力"<<'|'<<"生命值"<<'|'<<"类型"<<endl;
    cout<<role[1]->get_r_name()<<'|';
    cout<<*(role[1]);
    if(tower[1]!=NULL){
        cout<<"类型"<<"  |"<<"编号"<<'|'<<"攻击力"<<'|'<<"范围"<<'|'<<"攻击类型"<<endl;
        cout<<tower[1]->get_tower_type()<<"|";
        cout<<*tower[1];
    }
    PAUSE;
}
void Game::add_e(){
    CLR;
    int chiose_r;
    do{
    cout<<"请选择要添加的角色 一/二 ：";
    cin>>chiose_r;
    if(chiose_r!=1&&chiose_r!=2)
        cout<<setw(58)<<"选择错误，请重新选择！\n";
    }while(chiose_r!=1&&chiose_r!=2);
    chiose_r--;
    Equipment *e;
    cout<<"名称"<<"    |"<<"编号"<<'|'<<"攻击/防御"<<'|'<<"类型"<<endl;
    e=new B_F_Sword();
    cout<<e->get_e_name()<<"|";
    cout<<*e;
    delete e;
    e=new Warmog_s_Armor();
    cout<<e->get_e_name()<<"|";
    cout<<*e;
    delete e;
    e=new Infinity_Edge();
    cout<<e->get_e_name()<<"|";
    cout<<*e;
    delete e;
    e=new Thornmail();
    cout<<e->get_e_name()<<"|";
    cout<<*e;
    delete e;
    int state=0;
    bool ret;
    while(state==0){
        cout<<"请选择要添加的装备编号:";
        int chiose_e;
        cin>>chiose_e;
        switch (chiose_e) {
        case 1:{ret=role[chiose_r]->add_e(new B_F_Sword());state=1;}break;
        case 2:{ret=role[chiose_r]->add_e(new Warmog_s_Armor());state=1;}break;
        case 3:{ret=role[chiose_r]->add_e(new Infinity_Edge());state=1;}break;
        case 4:{ret=role[chiose_r]->add_e(new Thornmail());state=1;}break;
        default:{
                cout<<setw(58)<<"选择错误，请重新选择！\n";
            }
        }
    }
    if(ret==false)
        cout<<"添加失败!装备栏已满!";
    else {
        cout<<"添加成功!";
    }
    PAUSE;
}
void Game::add_tower(){
    CLR;
    int chiose_r;
    do{
    cout<<"请选择要添加的角色 一/二 ：";
    cin>>chiose_r;
    if(chiose_r!=1&&chiose_r!=2)
        cout<<setw(58)<<"选择错误，请重新选择！\n";
    }while(chiose_r!=1&&chiose_r!=2);
    chiose_r--;
    if(tower[chiose_r]!=NULL){
        cout<<"该角色已有防御塔!选择失败!";
        PAUSE;
        return;
    }
    Tower *t;
    cout<<"类型"<<"  |"<<"编号"<<'|'<<"攻击力"<<'|'<<"范围"<<'|'<<"攻击类型"<<endl;
    t=new Ordinary_tower();
    cout<<t->get_tower_type()<<"|";
    cout<<*t;
    delete t;
    t=new Highlands_tower();
    cout<<t->get_tower_type()<<"|";
    cout<<*t;
    delete t;
    int state=0;
    while(state==0){
        cout<<"请选择防御塔编号:";
        int chiose_t;
        cin>>chiose_t;
        switch (chiose_t) {
        case 1:{tower[chiose_r]=new Ordinary_tower();state=1;}break;
        case 2:{tower[chiose_r]=new Highlands_tower();state=1;}break;
        default:{
                cout<<setw(58)<<"选择错误，请重新选择！\n";
            }
        }
    }
    cout<<"添加成功!";
    PAUSE;
}
void Game::run(){
    CLR;
    int r1_hp=role[0]->get_hp();
    int r2_hp=role[1]->get_hp();
    while(r1_hp>0&&r2_hp>0){
        cout<<role[0]->get_r_name()<<" 发起攻击"<<endl;
        int damage=role[0]->get_damage()-role[1]->get_defense();
        if(damage<=0) {
            cout<<role[0]->get_r_name()<<"  造成了0伤害"<<endl;
            cout<<role[1]->get_r_name()<<"剩余血量为:"<<r2_hp<<endl;
        }
        else {
            r2_hp-=damage;
            cout<<role[0]->get_r_name()<<"  造成了"<<damage<<"伤害"<<endl;
            cout<<role[1]->get_r_name()<<"剩余血量为:"<<r2_hp<<endl;
        }
        if(tower[0]!=NULL){
            cout<<role[0]->get_r_name()<<" 的塔发起攻击"<<endl;
            int damage3=tower[0]->get_damage()-role[1]->get_defense();
            if(damage3<=0) {
                cout<<role[0]->get_r_name()<<"  的塔造成了0伤害"<<endl;
                cout<<role[1]->get_r_name()<<"剩余血量为:"<<r2_hp<<endl;
            }
            else {
                r2_hp-=damage3;
                cout<<role[0]->get_r_name()<<"  的塔造成了"<<damage3<<"伤害"<<endl;
                cout<<role[1]->get_r_name()<<"剩余血量为:"<<r2_hp<<endl;
            }
        }
        cout<<role[1]->get_r_name()<<" 发起攻击"<<endl;
        int damage1=role[1]->get_damage()-role[0]->get_defense();
        if(damage1<=0) {
            cout<<role[1]->get_r_name()<<"  造成了0伤害"<<endl;
            cout<<role[0]->get_r_name()<<"剩余血量为:"<<r1_hp<<endl;
        }
        else {
            r1_hp-=damage1;
            cout<<role[1]->get_r_name()<<"  造成了"<<damage1<<"伤害"<<endl;
            cout<<role[0]->get_r_name()<<"剩余血量为:"<<r1_hp<<endl;
        }
        if(tower[1]!=NULL){
            cout<<role[1]->get_r_name()<<" 的塔发起攻击"<<endl;
            int damage4=tower[1]->get_damage()-role[0]->get_defense();
            if(damage4<=0) {
                cout<<role[1]->get_r_name()<<"  的塔造成了0伤害"<<endl;
                cout<<role[0]->get_r_name()<<"剩余血量为:"<<r1_hp<<endl;
            }
            else {
                r1_hp-=damage4;
                cout<<role[1]->get_r_name()<<"  的塔造成了"<<damage4<<"伤害"<<endl;
                cout<<role[0]->get_r_name()<<"剩余血量为:"<<r1_hp<<endl;
            }
        }
        PAUSE;
    }
    if(r1_hp>0) cout<<role[0]->get_r_name()<<"胜利";
    else cout<<role[1]->get_r_name()<<"胜利";
    PAUSE;
}
void Game::Menu(){
    int state=0;
    int chiose;
    while(1){
        CLR;
        new_line(8);
        cout<<setw(55)<<"英雄联盟模拟器\n";
        new_line(2);
        cout<<setw(46)<<"1.开战\n";
        cout<<setw(58)<<"2.显示双方情况\n";
        cout<<setw(52)<<"3.添加装备\n";
        cout<<setw(55)<<"4.增加防御塔\n";
        cout<<setw(52)<<"0.退出系统\n";
        new_line(2);
        cout<<setw(44)<<"请选择:";
        cin>>chiose;
        switch (chiose) {
        case 1:run();break;
        case 2:Show_role();break;
        case 3:add_e();break;
        case 4:add_tower();break;
        case 0:state=1;break;
        default:{
            CLR;
            new_line(8);
            cout<<setw(58)<<"选择错误，请重新选择！\n";
            PAUSE;
            }
        }
        if(state==1) break;
    }
}

int main()
{
    Game game;
    if(game.welcome_face()){
        game.add_role();
        game.Menu();
    }
    return 0;
}
