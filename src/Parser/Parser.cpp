#include "Parser.h"

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
		return false;
	}

	getxmlSprites(&doc);
	getxmlVentana(&doc);
	getxmlFondos(&doc);
	getxmlObjetos(&doc);
	getxmlEstadosSprites(&doc);
	setAnchoJugador(&doc);
	setAltoJugador(&doc);
	setAnchoEscenario(&doc);
	setAltoEscenario(&doc);
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

	   objeto.tipo = HANDSHAKE_OBJETO_NUEVO;
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
			   if (!validar(estado) || atoi(estado.c_str())<1 || atoi(estado.c_str())>5)
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
			   if (!validar(orden) || atoi(orden.c_str())<1 || atoi(orden.c_str())>5)
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
