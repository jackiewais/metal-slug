#include "Parser.h"

Parser::Parser(){}

Parser::Parser(int cli)
{
 cliente = cli;

}

Parser::~Parser()
{
	listaSprites.clear();
	listaObjetos.clear();
	listaFondos.clear();
	listaEstadosSprites.clear();
}

bool Parser::parsearArchivoXML(const std::string& nameFileXML)
{
	std::stringstream ss;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(nameFileXML.c_str());

	if (!result)
	{
		pugi::xml_parse_result result = doc.load_file("Parser/game.xml");
		cout << "No se encontró el XML, se toma el de defecto" << endl;

		if (!result){
			cout << "ERROR abriendo XML" << endl;
			return false;
		}
	}
	getxmlCantJugadores(&doc);
	getxmlSprites(&doc);
	getxmlVentana(&doc);
	getxmlFondos(&doc);
	getxmlObjetos(&doc);
	getxmlEstadosSprites(&doc);
	setAnchoJugador(&doc);
	setAltoJugador(&doc);
	setAnchoEscenario(&doc);
	setAltoEscenario(&doc);
	getxmlEnemigos(&doc);
	getxmlBasicSprites(&doc);
	getxmlBonuses(&doc);
	getxmlPlataformas(&doc);
	getxmlBala(&doc);
	return true;
}
void Parser::getxmlSprites(const pugi::xml_document* doc)
{
	pugi::xml_node spritesNode = doc->child("sprites");
	for (pugi::xml_node i = spritesNode.first_child(); i; i = i.next_sibling())
	{
	   mensajeStruct sprite;
	   std::string objectId = i.child("objectId").first_child().value();
	   std::string ancho = i.child("ancho").first_child().value();
	   std::string alto = i.child("alto").first_child().value();
	   if (!validar(ancho))
	   			{
	   				ancho = "0";
	   			}
	   if (!validar(alto))
	  	   			{
	  	   				alto = "0";
	  	   			}

	   sprite.tipo = HANDSHAKE_SPRITES;
	   sprite.objectId = objectId;
	   sprite.message = ancho+";"+alto;
	   sprite.socketCli = cliente;
	   listaSprites.push_back(sprite);
	}
}
void Parser::getxmlVentana(const pugi::xml_document* doc)
{
	pugi::xml_node ventanaNode = doc->child("ventana");
	std::string objectId = ventanaNode.child("objectId").first_child().value();
	std::string ancho = ventanaNode.child("ancho").first_child().value();
	std::string alto = ventanaNode.child("alto").first_child().value();

	if (!validar(ancho))
		{
			ancho = "800";
		}
	if (!validar(alto))
		{
			alto = "600";
		}

	ventana.tipo = HANDSHAKE_DIMENSIONES_VENTANA;
	ventana.objectId = objectId;
	ventana.message = ancho+"x"+alto;
	ventana.socketCli = cliente;
}
void Parser::getxmlObjetos(const pugi::xml_document* doc)
{
	/*pugi::xml_node objetosNode = doc->child("objetos");
	pugi::xml_node elemNode = objetosNode.child("elementos");
	for (pugi::xml_node i = elemNode.first_child(); i; i = i.next_sibling())
	{
	   mensajeStruct objeto;
	   std::string objectId = i.child("objectId").first_child().value();
	   std::string imagen = i.child("imagen").first_child().value();
	   std::string x = i.child("x").first_child().value();
	   std::string y = i.child("y").first_child().value();
	   if (!validar(x))
	   			{
	   				x = "0";
	   			}
	   if (!validar(y))
	  	   		{
	  	   			y = "0";
	  	   		}

	   objeto.tipo = HANDSHAKE_OBJETO_NUEVO;
	   objeto.objectId = objectId;


	   string idObjToInt = objectId;
	   int idJugador = atoi(idObjToInt.erase(0, 1).c_str());
	   Jugador* jugador = this->escenarioS->getJugadorById(idJugador);
		string datosJug;
		if(jugador != NULL){
			datosJug = jugador->getStringMensaje();
		}else{
			datosJug = x + ";" + y + ";1;D";
		}
	   objeto.message = imagen + ";" + datosJug;
	   objeto.socketCli = cliente;
	   listaObjetos.push_back(objeto);
	}*/

	pugi::xml_node jugadoresNode = doc->child("jugadores");
	for (pugi::xml_node j = jugadoresNode.first_child(); j; j = j.next_sibling())
	{
	   mensajeStruct objeto;
	   std::string objectId = j.child("objectId").first_child().value();
	   std::string imagen = j.child("imagen").first_child().value();

	   objeto.tipo = HANDSHAKE_JUGADOR_NUEVO;
	   objeto.objectId = objectId;
		objeto.message = imagen;
		objeto.socketCli = cliente;
		listaObjetos.push_back(objeto);
	}
}
void Parser::getxmlFondos(const pugi::xml_document* doc)
{
fondo capas[] = { {"A",1}, {"B",1}, {"C",1}, {"D",1}, {"E",1}, {"F",1}, {"G",1}, {"H",1}, {"I",1}, {"J",1}};

	pugi::xml_node fondosNode = doc->child("fondos");
	for (pugi::xml_node i = fondosNode.first_child(); i; i = i.next_sibling())
	{
	   mensajeStruct fondo;
	   std::string imagen = i.child("imagen").first_child().value();
	   std::string ancho = i.child("ancho").first_child().value();
	   std::string alto = i.child("alto").first_child().value();
	   std::string zIndex = i.child("zIndex").first_child().value();
	   if (!validar(ancho))
	   			{
	   				ancho = "0";
	   			}
	   if (!validar(alto))
	  	   		{
	  	   			alto = "0";
	  	   		}
	   if (!validar(zIndex))
	  	   		{
	  	   			zIndex = "1";
	  	   		}
	   else{
		   int sizeCapas = (sizeof((capas))/sizeof((capas[0])));
		   if ( sizeCapas < atoi(zIndex.c_str()) || atoi(zIndex.c_str())< 0){
			     zIndex = "1";
		   }
	   }
	   stringstream ss;
	   ss << capas[atoi(zIndex.c_str())-1].numero;
	   if (capas[atoi(zIndex.c_str())-1].numero <= 9){
		   fondo.objectId = capas[atoi(zIndex.c_str())-1].letra + "0"+ ss.str();
	   }else{
		   fondo.objectId = capas[atoi(zIndex.c_str())-1].letra + ss.str();
	   }

	   fondo.tipo = HANDSHAKE_FONDO_NUEVO;
	   fondo.message = imagen+";"+ancho+";"+alto;
	   fondo.socketCli = cliente;
	   listaFondos.push_back(fondo);
	   capas[atoi(zIndex.c_str())-1].numero = capas[atoi(zIndex.c_str())-1].numero + 1;
	}
}
void Parser::getxmlEstadosSprites(const pugi::xml_document* doc)
{
	pugi::xml_node esSpritesNode = doc->child("estadosSprites");
	for (pugi::xml_node j = esSpritesNode.first_child(); j; j = j.next_sibling())
	{
		std::string objetId = j.attribute("objetId").value();
		for (pugi::xml_node i = j.first_child() ; i; i = i.next_sibling())
		{
			   mensajeStruct esSprite;
			   std::string estado = i.child("estado").first_child().value();
			   std::string ancho = i.child("ancho").first_child().value();
			   std::string alto = i.child("alto").first_child().value();
			   std::string cantidad = i.child("cantidad").first_child().value();
			   std::string orden = i.child("orden").first_child().value();
			   if (!validar(estado) || atoi(estado.c_str())<1)
						{
							estado = "1";
						}
			   if (!validar(ancho))
						{
							ancho = "37";
						}
			   if (!validar(alto))
						{
							alto = "49";
						}
			   if (!validar(cantidad))
						{
							cantidad = "3";
						}
			   if (!validar(orden) || atoi(orden.c_str())<1)
						{
							orden = "1";
						}

			   esSprite.tipo = HANDSHAKE_ESTADO_SPRITE;
			   esSprite.objectId = objetId;
			   esSprite.message = estado+ ";"+ancho+";"+alto+";"+cantidad+";"+orden;
			   esSprite.socketCli = cliente;
			   listaSprites.push_back(esSprite);
		}
	}
}

void Parser::getxmlEnemigos(const pugi::xml_document* doc)
{
	pugi::xml_node enemigosNode = doc->child("enemigos");
	for (pugi::xml_node i = enemigosNode.first_child(); i; i = i.next_sibling())
	{
	   enemigoStruct enemigo;
	   std::string ancho = i.child("ancho").first_child().value();
	   std::string alto = i.child("alto").first_child().value();
	   std::string velocidad = i.child("velocidad").first_child().value();
	   std::string posXAbsolutaDeJugadorParaAparicion = i.child("posXAbsolutaDeJugadorParaAparicion").first_child().value();
	   std::string bloquearAvanceEscenario = i.child("bloquearAvanceEscenario").first_child().value();
	   std::string aparecePorIzq = i.child("aparecePorIzq").first_child().value();
	   string sprite = i.child("sprite").first_child().value();
	   if (!validar(ancho)){
		   ancho = "0";
	   }
	   if (!validar(alto)){
		   alto = "0";
	   }
	   if (!validar(velocidad)){
		   velocidad = "1";
	   }
	   if (!validar(posXAbsolutaDeJugadorParaAparicion)){
		   posXAbsolutaDeJugadorParaAparicion = "0";
	   }
	   if (!validar(bloquearAvanceEscenario)){
		   bloquearAvanceEscenario = "0";
	   }
	   if (!validar(aparecePorIzq)){
		   aparecePorIzq = "0";
	   }

	   enemigo.ancho = atoi(ancho.c_str());
	   enemigo.alto = atoi(alto.c_str());
	   enemigo.velocidad = atoi(velocidad.c_str());
	   enemigo.posXAbsolutaDeJugadorParaAparicion = atoi(posXAbsolutaDeJugadorParaAparicion.c_str());
	   enemigo.bloquearAvanceEscenario = atoi(bloquearAvanceEscenario.c_str());
	   enemigo.aparecePorIzq = atoi(aparecePorIzq.c_str());
	   enemigo.sprite = sprite;
	   listaEnemigos.push_back(enemigo);
	}
}
void Parser::getxmlBasicSprites(const pugi::xml_document* doc)
{

	pugi::xml_node spritesNode = doc->child("basicSprites");
		for (pugi::xml_node i = spritesNode.first_child(); i; i = i.next_sibling())
		{
		   mensajeStruct spriteMsj;
		   std::string objectId = i.child("id").first_child().value();
		   std::string sprite = i.child("sprite").first_child().value();
		   std::string ancho = i.child("ancho").first_child().value();
		   std::string alto = i.child("alto").first_child().value();
		   std::string frames = i.child("frames").first_child().value();

		   spriteMsj.tipo = HANDSHAKE_GRAFIC_BASIC;
		   spriteMsj.objectId = objectId;
		   spriteMsj.message = sprite+";"+ancho+";"+alto+";"+frames;
		   spriteMsj.socketCli = cliente;
		   listaSprites.push_back(spriteMsj);
		}
}


void Parser::getxmlBonuses(const pugi::xml_document* doc)
{
	pugi::xml_node bonusesNode = doc->child("bonuses");
	int id = 0;
	for (pugi::xml_node i = bonusesNode.first_child(); i; i = i.next_sibling())
	{
		id++;
		bonus bonus;
		bonus.type = static_cast<bonusTypes>(atoi(i.child("type").first_child().value()));
		bonus.posXAbs =  atoi(i.child("posXAbs").first_child().value());
		bonus.posX =  bonus.posXAbs;
		bonus.posY =  atoi(i.child("posYAbs").first_child().value());
		bonuses[id]=bonus;
	}
}

bool Parser::validar(std::string numero)
{
	 if (numero.empty()) return false;
	   int  tam = numero.size();
		 for( int i=0 ; i<tam ; i++ ){
		   if (!std::isdigit(numero[i])){
	          return false;
		   }
	     }
	 return true;
}
void Parser::getxmlCantJugadores(const pugi::xml_document* doc) {
	this->cantJugadores = atoi(doc->child_value("cantidadJugadores"));
}

void Parser::setAnchoJugador(const pugi::xml_document* doc) {

	pugi::xml_node fisicoJugadorNode = doc->child("fisicoJugador");
	this->anchoJugador = fisicoJugadorNode.child("ancho").first_child().value();
}

void Parser::setAltoJugador(const pugi::xml_document* doc) {

	pugi::xml_node fisicoJugadorNode = doc->child("fisicoJugador");
	this->altoJugador = fisicoJugadorNode.child("alto").first_child().value();
}

void Parser::setAnchoEscenario(const pugi::xml_document* doc) {

	pugi::xml_node ventanaNode = doc->child("ventana");
	this->anchoEscenario = ventanaNode.child("ancho").first_child().value();
}

void Parser::setAltoEscenario(const pugi::xml_document* doc) {

	pugi::xml_node ventanaNode = doc->child("ventana");
	this->altoEscenario = ventanaNode.child("alto").first_child().value();
}
int Parser::getCantJugadores() {
	return this->cantJugadores;
}

int Parser::getAnchoJugador() {
	return atoi(this->anchoJugador.c_str());
}

int Parser::getAltoJugador() {
	return atoi(this->altoJugador.c_str());
}

int Parser::getAnchoEscenario() {
	return atoi(this->anchoEscenario.c_str());
}

int Parser::getAltoEscenario() {
	return atoi(this->altoEscenario.c_str());
}
void Parser::getxmlPlataformas(const pugi::xml_document* doc)
{

	pugi::xml_node plataformasNode = doc->child("plataformas");
	for (pugi::xml_node i = plataformasNode.first_child(); i; i = i.next_sibling())
	{
			   mensajeStruct esPlataforma;
			   std::string objectId = i.child("objectId").first_child().value();
			   std::string imagen = i.child("imagen").first_child().value();
			   std::string ancho = i.child("ancho").first_child().value();
			   std::string alto = i.child("alto").first_child().value();
			   std::string posX = i.child("posX").first_child().value();
			   std::string posY = i.child("posY").first_child().value();
			   if (!validar(objectId))
						{
				            objectId = "1";
						}
			   if (!validar(ancho))
						{
							ancho = "37";
						}
			   if (!validar(alto))
						{
							alto = "49";
						}
			   if (!validar(posX))
						{
							posX = "0"; //poner random
						}
			   if (!validar(posY))
						{
							posY = "100"; //dar tope
						}

			   esPlataforma.tipo = PLATAFORMA_NEW;
			   esPlataforma.objectId = objectId;//imagen;
			   esPlataforma.message = imagen+";"+ancho+";"+alto+";"+posX;
			   esPlataforma.socketCli = cliente;
			   listaPlataformas.push_back(esPlataforma);
		}
}
void Parser::getxmlBala(const pugi::xml_document* doc)
{
	pugi::xml_node balaNode = doc->child("balas");
	std::string imagen = balaNode.child("imagen").first_child().value();
	std::string ancho = balaNode.child("ancho").first_child().value();
	std::string alto = balaNode.child("alto").first_child().value();
	std::string velocidad = balaNode.child("velocidad").first_child().value();

	if (!validar(ancho))
		{
			ancho = "10";
		}
	if (!validar(alto))
		{
			alto = "10";
		}
	if (!validar(velocidad))
		{
			alto = "10";
		}
	bala.tipo = BALA_NEW;
	bala.message = imagen+";"+ancho+";"+alto+";"+velocidad;
	bala.socketCli = cliente;

	this->velocidadBala = atoi(velocidad.c_str());
}
