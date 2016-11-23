#include "Escenario.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

Escenario::Escenario() {
	this->gWindow = NULL;
	this->gRenderer = NULL;
	// Valores por defecto
	this->screenWidth = 800;
	this->screenHeight = 600;
	cargarMensajeEsperandoJugador();
	numero = new Numero();
	progreso = new Progreso ();
	lbalas = new Label();
	lGameOver = new Label();
	gameOver=false;
}

void Escenario::cargarMensajeEsperandoJugador(){
/*
this->addSprite("foo",0,0);
this->crearObjeto("PAUSA","foo",this->screenWidth/3,10,PARADO,"C");
*/
}
Escenario::~Escenario() {
	// TODO Auto-generated destructor stub
}

bool Escenario::init()
{
	this->gameOver=false;
	this->gameOverAll=false;
	this->endOfLevel=false;

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "METAL-SLUG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	this->running=true;
	return success;
}

LTexture* Escenario::addSprite(std::string idSprite, int ancho, int alto) {
	LTexture *textura;

	textura = new LTexture(this, "images/" + idSprite + ".png");
	this->mapTexturas[idSprite] = textura;


	if (ancho != 0)
		textura->setWidth(ancho);
	if (alto != 0)
		textura->setHeight(alto);
	return textura;
}

void Escenario::addGraficableBasic(string id, string sprite, int ancho, int alto, int frames) {

	GraficableBasic* graficable = new GraficableBasic();
	graficable->initTexture(sprite,ancho,alto,frames);
	this->graficablesBasic[id] = graficable;

}

Numero* Escenario::crearNumero(std::string idSprite, int ancho, int alto  ) {

	this->numero->initTexture("images/" + idSprite + ".png", ancho,alto);
	return this->numero;
}

Progreso* Escenario::crearProgreso(std::string idSprite, int ancho, int alto  ) {

	this->progreso->initTexture("images/" + idSprite + ".png", ancho,alto);
	return this->progreso;
}

Contador* Escenario::crearContador(string id, int puntaje, int vida, int municiones){
	string idCopy = id;
	idCopy.erase(0,1);
	int x = 5 + (atoi(idCopy.c_str())-1) * 200;
	Contador* contador = new Contador(id,x,10,this->numero,this->progreso,this->lbalas,puntaje,vida,municiones);
	this->contadores[id]= contador;
	return contador;


}
void Escenario::agregarEstado(string idSprite, estadoJugador estado, int anchoFrame, int altoFrame, int cantFrames, int ordenEstado) {
	// Si el objeto esta en el map
	if ( this->mapTexturas.find(idSprite) != this->mapTexturas.end() ) {
		this->mapTexturas[idSprite]->agregarEstado(estado, anchoFrame, altoFrame, cantFrames,ordenEstado);
	}
}

void Escenario::crearJugadorPrincipal(mensajeStruct msg){
	this->jugadorPrincipal = this->mapObjetosGraficables[msg.objectId];
}


bool Escenario::loadMedia()
{
	LTexture *textura;
	std::map<std::string, LTexture*>::iterator it;

	for (it = this->mapTexturas.begin(); it != this->mapTexturas.end(); it++) {
		textura = it->second;

		if( !textura->loadFromFile() ) {
			printf( "Failed to load texture image!\n" );
			textura->free();
			// Como no se pudo cargar la imagen se carga una por defecto
			textura->setPath("images/default.png");
			if ( !textura->loadFromFile() ) {
				textura->free();
				return false;
			}
		}
	}

	for (map<string, GraficableBasic*>::iterator it = this->graficablesBasic.begin(); it != this->graficablesBasic.end(); it++) {
			it->second->loadMedia(this->gRenderer);
	}


	this->numero->loadMedia(this->gRenderer);
	this->progreso->loadMedia(this->gRenderer);

	this->balas.loadMedia(this->gRenderer);

	this->lbalas->setData(this->gRenderer,"ARMS",36);
	this->lGameOver->setData(this->gRenderer,"GAME OVER",72);
	/*this->iGameOver->initTexture("game_over",800,600);
	this->iGameOver->loadMedia(this->gRenderer);
	this->iFondoNegro->initTexture("fondonegro",800,600);
	this->iFondoNegro->loadMedia(this->gRenderer);*/
	return true;
}
void Escenario::moverFondo(mensajeStruct msg){
	int desplA = 0;
	int posA = atoi(msg.message.c_str());
	desplA = posA;
  /*	if(posA<=-this->screenWidth){

		desplA+=this->screenWidth;
	}*/
	std::map<std::string, ObjetoGraficable*>::iterator it;
	for (it = this->mapFondos.begin(); it != this->mapFondos.end(); it++) {
		it->second->actualizarPosicionFondo(desplA);

	}
}

void Escenario::addFondo(std::string objectId) {
	this->mapFondos[objectId] = this->mapObjetosGraficables[objectId];
}

void Escenario::calcularParallax() {
	std::map<std::string, ObjetoGraficable*>::iterator it;
	int despA = 0 ;
	this->fondoMasChico = this->mapFondos.begin()->second->getAncho();
	cout << "primer fondo " << fondoMasChico <<endl;
	//ME FIJO CUAL DE TODOS LOS FONDOS TIENE LA DIMENSION MAS CHICA
	for (it = this->mapFondos.begin(); it != this->mapFondos.end(); it++) {
		if (this->fondoMasChico >= it->second->getAncho()){
			this->fondoMasChico = it->second->getAncho();
		    }
	}
	//CALCULO EL PARALLAX PARA TODOS
	cout << "el fondo más chico es : " << this->fondoMasChico << endl;
	despA = this->fondoMasChico - this->screenWidth;
	for (it = this->mapFondos.begin(); it != this->mapFondos.end(); it++) {
		it->second->setFactorParallax(despA, this->screenWidth);
		}
}

void Escenario::close()
{
	std::map<std::string, LTexture*>::iterator it;
	//Free loaded images
	for (it = this->mapTexturas.begin(); it != this->mapTexturas.end(); it++) {
		it->second->free();
	}
	this->mapTexturas.clear();
	std::map<std::string, ObjetoGraficable*>::iterator itOb;
	for (itOb = this->mapObjetosGraficables.begin(); itOb != this->mapObjetosGraficables.end(); itOb++) {
		delete itOb->second;
	}
	this->mapObjetosGraficables.clear();
	/*std::map<std::string, ObjetoGraficable*>::iterator itObF;
	for (itObF = this->mapFondos.begin(); itObF != this->mapFondos.end(); itObF++) {
		delete itObF->second;
	}*/
	this->mapFondos.clear();

	for (map<string, Contador*>::iterator itCont = this->contadores.begin(); itCont != this->contadores.end(); itCont++) {
		delete itCont->second;
	}
	this->contadores.clear();

	 for (std::list<Label*>::iterator it=this->eoLevelLabels.begin(); it != this->eoLevelLabels.end(); ++it){
		delete (*it);
	 }
	 this->eoLevelLabels.clear();

	for (map<std::string, GraficableBasic*>::iterator  itOb = this->graficablesBasic.begin(); itOb != this->graficablesBasic.end(); itOb++) {
		delete itOb->second;
	}
	this->graficablesBasic.clear();
	for (map<int, Bonus*>::iterator  itOb = this->bonuses.begin(); itOb != this->bonuses.end(); itOb++) {
		delete itOb->second;
	}
	this->bonuses.clear();

	for (list<Label*>::iterator it=eoLevelLabels.begin(); it != eoLevelLabels.end(); ++it){
		delete (*it);
	 }
	this->eoLevelLabels.clear();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );

	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	numero->close();
	progreso->close();
	lbalas->close();
	lGameOver->close();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	this->running=false;
}

SDL_Renderer* Escenario::getGRenderer()
{
	return this->gRenderer;
}
void Escenario::setDimensiones(int screenWidth, int screenHeight){
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void Escenario::crearObjeto(std::string idObj, std::string idSprite, int x, int y, estadoJugador estado, string conectado) {
	// Se comprueba que el sprite haya sido cargado antes
	if ( this->mapTexturas.find(idSprite) != this->mapTexturas.end() ) {
		LTexture *textura = this->mapTexturas[idSprite];
		this->mapObjetosGraficables[idObj] = new ObjetoGraficable(idObj, textura, x, y);
		this->mapObjetosGraficables[idObj]->setGrisado((conectado == "D"));
	}
}

void Escenario::crearBonus(int id, int x, int y, bonusTypes bonus) {
	GraficableBasic* grafBonus = this->graficablesBasic["bonus"];
	this->bonuses[id] = new Bonus();
	this->bonuses[id]->init(grafBonus,bonus,x,y);
}
void Escenario::updateBonus(int id, int x, int y, bonusTypes bonus) {
	if ( this->bonuses.find(id) == this->bonuses.end()){
		this->crearBonus(id,x,y,bonus);
	}else{
		this->bonuses[id]->setPosicion(x,y);
	}
}

void Escenario::deleteBonus(int id) {
	if ( this->bonuses.find(id) != this->bonuses.end() ) {
		delete this->bonuses[id];
		this->bonuses.erase(id);
	}
}

void Escenario::actualizarEnemigo(std::string idObj, int x, int y) {
	// Si el objeto esta en el map
	if ( this->mapObjetosGraficables.find(idObj) != this->mapObjetosGraficables.end() ) {
		cout<<"actualiza pos enemigo, posX: "<<x<<endl;
		ObjetoGraficable* objeto = this->mapObjetosGraficables[idObj];
		objeto->actualizarPosicion(x, y);
	}
}

void Escenario::renderizarObjetos() {
	try{
	SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( this->gRenderer );

	if (this->gameOverAll){
		this->graficablesBasic["game_over"]->render(0,0);
	}else if (this->endOfLevel) {
		this->graficablesBasic["fondo_negro"]->render(0,0);
		 for (list<Label*>::iterator it=eoLevelLabels.begin(); it != eoLevelLabels.end(); ++it){
		    (*it)->renderDefault();
		 }

	}else{
		std::map<std::string, ObjetoGraficable*>::iterator it;
		for (it = this->mapObjetosGraficables.begin(); it != this->mapObjetosGraficables.end(); it++) {
			it->second->actualizarGrisado();

			if(this->jugadorPrincipal->id != it->second->id){
				if(it->second->id != "PAUSA"){
				it->second->render();
				}
			}
		}

		this->jugadorPrincipal->render();

		//Render Bonuses
		for (map<int, Bonus*>::iterator it = this->bonuses.begin(); it != this->bonuses.end(); it++) {
			it->second->render();
		}


		if(!(this->balas.balas.empty())){
		this->balas.render();
		this->balas.balas.clear();
		}
		for (map<string, Contador*>::iterator itcont = this->contadores.begin(); itcont != this->contadores.end(); itcont++) {
			itcont->second->renderizar();
		}

		if(!this->esperandoJugadores){
			this->renderPausa();
		}

		if (this->gameOver){
			lGameOver->render(200,200);
		}
	}
	SDL_RenderPresent( this->gRenderer );
	}catch(...){
		cout << "Problemas con el render" << endl;
	}
}
void Escenario::renderPausa(){

	this->mapObjetosGraficables["PAUSA"]->render();
}



void Escenario::actualizarPosicionObjeto(std::string idObj, int x, int y, estadoJugador estado, string conectado) {
	// Si el objeto esta en el map
	if ( this->mapObjetosGraficables.find(idObj) != this->mapObjetosGraficables.end() ) {
		ObjetoGraficable* objeto = this->mapObjetosGraficables[idObj];
		objeto->actualizarPosicion(x, y);
		objeto->setGrisado((conectado == "D"));
		objeto->actualizarEstado(estado);
	}
}


void Escenario::eliminarObjeto(std::string idObj) {
	// Si el objeto esta en el map
	if ( this->mapObjetosGraficables.find(idObj) != this->mapObjetosGraficables.end() ) {
		delete this->mapObjetosGraficables[idObj];
		this->mapObjetosGraficables.erase(idObj);
	}
}

void Escenario::setGameOverAll(){
	this->gameOverAll = true;
}

void Escenario::setGameOverMe(){
	this->gameOver = true;
}

bool Escenario::isGameOver(){
	return this->gameOver || this->gameOverAll;
}


void Escenario::addEOLevelLabel(string name, int posX, int posY){
	Label* label = new Label();
	label->setData(this->gRenderer,name,48);
	label->setDefaultPos(posX,posY);
	this->eoLevelLabels.push_back(label);
}
