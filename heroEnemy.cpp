#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Enemy;    //前方宣言

const int MAX_NAME = 16;

class Hero {
public:
    Hero(char* pName, int hp);
    ~Hero();

public:
    int getDiffence() {    return _diffence;    }
    int getHp() {   return _hp;     }
    void setHp(int hp) {    _hp = hp; }
    void show();

public:
    void attack(Enemy* enemy);
    void heal();

private:
    char* _pName;
    int _nameSize;

private:
    int _hp = 0;
    int _attack = 75;
    int _diffence = 20;
};

// コンストラクタ
Hero::Hero(char* pName, int hp) {

    // 名前をコピー
    _nameSize = strlen(pName);
    _pName = new char[_nameSize + 1];   // +1は\0分
    strcpy(_pName, pName);

    // 他のパラメータ初期化
    _hp = hp;
    _attack = 75;
    _diffence = 20;
}

// デストラクタ
Hero::~Hero() {
    if (_pName != NULL)
    {
        delete[] _pName;
        _pName = NULL;
    }
}

void Hero::show() {
    printf("名前：%s\n", _pName);
    printf("体力：%d\n", _hp);
    printf("攻撃力：%d, ", _attack);
    printf("防御力：%d\n", _diffence);
}


class Enemy {
public:
    Enemy(char* pName, int hp);
    ~Enemy();

    void operator*(const int i);

public:
    int getDiffence() { return _diffence; }
    int getHp() { return _hp; }
    void setHp(int hp) { _hp = hp; }
    void show();

public:
    void attack(Hero* hero);
    void heal();

private:
    char* _pName;
    int _nameSize;

private:
    int _hp = 0;
    int _attack = 75;
    int _diffence = 20;
};

void Enemy::operator*(const int i)
{
    _hp *= i;
    _attack *= i;
    _diffence *= i;
}

// コンストラクタ
Enemy::Enemy(char* pName, int hp) {

    // 名前をコピー
    _nameSize = strlen(pName);
    _pName = new char[_nameSize + 1];   // +1は\0分
    strcpy(_pName, pName);

    // 他のパラメータ初期化
    _hp = hp;
    _attack = 75;
    _diffence = 20;
}

// デストラクタ
Enemy::~Enemy() {
    if (_pName != NULL)
    {
        delete[] _pName;
        _pName = NULL;
    }
}

void Enemy::show() {
    printf("名前：%s\n", _pName);
    printf("体力：%d\n", _hp);
    printf("攻撃力：%d, ", _attack);
    printf("防御力：%d\n", _diffence);
}


//
//Hero InputHeroStatus() {
//    char name[MAX_NAME]{ "" };
//    int hp = 0;
//
//    printf("ヒーロー名を入力\n> ");
//    cin >> name;
//    printf("HPを入力\n> ");
//    cin >> hp;
//
//    Hero hero(&name[0], hp);
//
//    // ステータス表示
//    hero.show();
//
//    return hero;
//}

//Enemy InputEnemyStatus() {
//    char name[MAX_NAME]{ "" };
//    int hp = 0;
//
//    printf("エネミー名を入力\n> ");
//    cin >> name;
//    printf("HPを入力\n> ");
//    cin >> hp;
//
//    Enemy enemy(&name[0], hp);
//
//    // ステータス表示
//    enemy.show();
//
//    return enemy;
//}

void Hero::attack(Enemy* enemy) {
    int deffence = enemy->getDiffence();
    int damage = 0;
    damage = _attack - deffence;
    printf("%sの攻撃！\n%dのダメージを与えた\n", _pName, damage);

    int hp = enemy->getHp();
    enemy->setHp(hp - damage);
    printf("相手の残りHP : %d\n", enemy->getHp());
}

void Enemy::attack(Hero* hero) {
    int deffence = hero->getDiffence();
    int damage = 0;
    damage = _attack - deffence;
    printf("%sの攻撃！\n%dのダメージを与えた\n", _pName, damage);

    int hp = hero->getHp();
    hero->setHp(hp - damage);
    printf("相手の残りHP : %d\n", hero->getHp());
}

void Hero::heal() {
    int healHp = 0;
    printf("どのくらい回復しますか\n> ");
    cin >> healHp;
    _hp += healHp;

    printf("%sの残りHP : %d\n", _pName, _hp);
}

void Enemy::heal() {
    int healHp = 0;
    printf("どのくらい回復しますか\n> ");
    cin >> healHp;
    _hp += healHp;

    printf("%sの残りHP : %d\n", _pName, _hp);
}

int main()
{
    bool turn = false;
    //Hero hero = InputHeroStatus();
    //Enemy enemy = InputEnemyStatus();
    char name[MAX_NAME]{ "" };
    int hp = 0;

    printf("ヒーロー名を入力\n> ");
    cin >> name;
    printf("HPを入力\n> ");
    cin >> hp;

    Hero hero(&name[0], hp);

    // ステータス表示
    hero.show();

    printf("エネミー名を入力\n> ");
    cin >> name;
    printf("HPを入力\n> ");
    cin >> hp;

    Enemy enemy(&name[0], hp);

    // ステータス表示
    enemy.show();


    int select = 0;
    while (true) {
        // プレイヤーターン
        printf("攻撃 : 1\, 回復 : 2\n> ");
        cin >> select;

        switch (select)
        {
        case 1:
            hero.attack(&enemy);
            break;
        case 2:
            hero.heal();
            break;
        default:
            break;
        }
        if (enemy.getHp() <= 0) { break; }

        // エネミーターン
        printf("攻撃 : 1\, 回復 : 2\n> ");
        cin >> select;

        switch (select)
        {
        case 1:
            enemy.attack(&hero);
            break;
        default:
            break;
        }
        if (hero.getHp() <= 0) { break; }
    }
}