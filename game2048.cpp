#include "game2048.h"
#include "ui_game2048.h"
#include <QKeyEvent>
#include<iostream>

game2048::game2048(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::game2048)
{
    ui->setupUi(this);
    resize(800,400);
    board=new int* [boardlen];
    for(int i=0;i<boardlen*boardlen;i++){
        boardblock[i]=findChild<QLabel*>("block_"+QString::number(i+1));
    }
    for(int i=0;i<boardlen;i++){
        board[i]=new int[boardlen];
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            board[i][j]=0;
        }
    }
    ui->res_label->setVisible(false);
    ui->next_button->setVisible(false);
    score=0;
    flush();
    this->grabKeyboard();
}

game2048::~game2048()
{
    for(int i=0;i<boardlen;i++){
        delete boardblock[i];
    }
    delete ui;
}


void game2048::addone(){
    bool space=false;
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            if(board[i][j]==0)
                space=true;
        }
    }
    if(!space)
        return;
    int i,j;
    do{
        i=rand()%boardlen;
        j=rand()%boardlen;
    }while(board[i][j]!=0);
    int temp=(rand()%2+1)*2;
    board[i][j]=temp;
    //return true;
}
void game2048::flush(){
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            if(board[i][j]!=0)
                boardblock[i*boardlen+j]->setText(QString::number(board[i][j]));
            else
                boardblock[i*boardlen+j]->setText("");
        }
    }
    ui->label->setText("得分:"+QString::number(score));
    if(judge()){
        if(score>=500){
            ui->res_label->setText("通过！请进入下一关");
            ui->res_label->setVisible(true);
            ui->next_button->setVisible(true);
        }
    }else{
        ui->res_label->setText("失败，请再次尝试");
        ui->res_label->setVisible(true);
    }
}

void game2048::move_up(){
    for(int j=0;j<boardlen;j++){
        int k=0;
        for(int i=0;i<boardlen;i++){
            if(board[i][j]!=0){
                if(k!=i){
                    board[k][j]=board[i][j];
                    board[i][j]=0;
                }
                k++;
            }
        }
    }
    for(int j=0;j<boardlen;j++){
        for(int i=0;i<boardlen-1;i++){
            if(board[i][j]==board[i+1][j]&&board[i][j]!=0){
                score+=board[i][j];
                board[i][j]*=2;
                board[i+1][j]=0;
            }
        }
    }
    for(int j=0;j<boardlen;j++){
        int k=0;
        for(int i=0;i<boardlen;i++){
            if(board[i][j]!=0){
                if(k!=i){
                    board[k][j]=board[i][j];
                    board[i][j]=0;
                }
                k++;
            }
        }
    }
}
void game2048::down(){
    for(int j=0;j<boardlen;j++){
        for(int i=0;i<boardlen/2;i++){
            int tmp=board[i][j];
            board[i][j]=board[boardlen-1-i][j];
            board[boardlen-1-i][j]=tmp;
        }
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            if(board[i][j]!=0){
                qDebug()<<i<<" "<<j<<" :"<<board[i][j];
            }
        }
    }
    move_up();
    for(int j=0;j<boardlen;j++){
        for(int i=0;i<boardlen/2;i++){
            int tmp=board[i][j];
            board[i][j]=board[boardlen-1-i][j];
            board[boardlen-1-i][j]=tmp;
        }
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            if(board[i][j]!=0){
                qDebug()<<i<<" "<<j<<" :"<<board[i][j];
            }
        }
    }
    addone();
    flush();
}
void game2048::right(){
    int tmp[boardlen][boardlen];
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            tmp[i][j]=board[j][boardlen-1-i];
        }
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            board[i][j]=tmp[i][j];
        }
    }
    move_up();
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            tmp[i][j]=board[boardlen-1-j][i];
        }
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            board[i][j]=tmp[i][j];
        }
    }
    addone();
    flush();
}
void game2048::left(){
    int tmp[boardlen][boardlen];
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            tmp[i][j]=board[boardlen-1-j][i];
        }
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            board[i][j]=tmp[i][j];
           // debugString+=QString::number(board[i][j])+" ";
        }
       // debugString+="\n";
    }
    move_up();
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            tmp[i][j]=board[j][boardlen-1-i];
        }
    }
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            board[i][j]=tmp[i][j];
          // debugString+=QString::number(board[i][j])+" ";
        }
       // debugString+="\n";
    }
    //qDebug()<<debugString;
    addone();
    flush();
}
void game2048::up(){
    move_up();
    addone();
    flush();
}
void game2048::init(){
    score=0;
    for(int i=0;i<boardlen;i++){
        for(int j=0;j<boardlen;j++){
            board[i][j]=0;
        }
    }
    addone();
    addone();
    ui->res_label->setVisible(false);
    flush();
   // setLayout(layout);
}

void game2048::on_start_button_clicked()
{
    init();
}
void game2048::keyPressEvent(QKeyEvent *e)
{
    if(has_res)
        return;
    switch (e->key())
    {
    case Qt::Key_Up:up();break;
    case Qt::Key_Down :down(); break;
    case Qt::Key_Left : left(); break;
    case Qt::Key_Right : right();break;
    }
}
bool game2048::judge(){
    if(score>=500){
        return true;
        has_res=true;
    }
    else{
        for(int i=0;i<boardlen;i++){
            for(int j=0;j<boardlen;j++){
                if(board[i][j]==0)
                    return true;
            }
        }
        for(int i=0;i<boardlen-1;i++){
            for(int j=0;j<boardlen;j++){
                if(board[i][j]==board[i+1][j])
                    return true;
            }
        }
        for(int i=0;i<boardlen;i++){
            for(int j=0;j<boardlen-1;j++){
                if(board[i][j]==board[i][j+1])
                    return true;
            }
        }
        has_res=true;
        return false;
    }
}
