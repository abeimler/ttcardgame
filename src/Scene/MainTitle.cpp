#include <Scene/MainTitle.hpp>

void MainTitle::Init(){
    this->mainFont.x = 64;
    this->mainFont.y = 450;

    std::vector<std::string> strMainOption (4);
    strMainOption[0] = "Neues Spiel (2 Player | 3x3 Field)";
    strMainOption[1] = "Neues Spiel (3 Player | 4x4 Field)";
    strMainOption[2] = "Neues Spiel (4 Player | 5x5 Field)";
    strMainOption[3] = "Verlassen";

    this->mainFont.addStringList(0,0,strMainOption);

    F2CLoadBitmapintoSprite(this->bgTitle,graphicDir+"title.png");
}
void MainTitle::Update(){
    this->mainFont.update();
    switch(this->mainFont.getIndex()){
        case 0:
            Engine::Game.ChangeState(new GamePlay (2,5,3,3));
        break;
        case 1:
            Engine::Game.ChangeState(new GamePlay (3,6,4,4));
        break;
        case 2:
            Engine::Game.ChangeState(new GamePlay (4,7,5,5));
        break;
        case 3:
            Engine::Game.Quit();
        break;
    }
}
void MainTitle::Render(){
    this->bgTitle.render();
    this->mainFont.render();
}
