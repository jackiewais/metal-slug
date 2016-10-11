#include "Parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{
	listaSprites.clear();
	listaObjetos.clear();
	listaFondos.clear();
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
	return true;
}
void Parser::getxmlSprites(const pugi::xml_document* doc)
{
	pugi::xml_node spritesNode = doc->child("sprites");
	std::string tipo = spritesNode.child("tipo").first_child().value();
	   if (!validar(tipo))
	   			{
	   				tipo = "20";
	   			}
	for (pugi::xml_node i = spritesNode.first_child(); i; i = i.next_sibling())
	{
	   mensajeStruct sprite;
	   std::string objectId = i.child("objectId").first_child().value();
	   std::string ancho = i.child("ancho").first_child().value();
	   std::string alto = i.child("alto").first_child().value();
	   if (!validar(ancho))
	   			{
	   				ancho = "5";
	   			}
	   if (!validar(alto))
	  	   			{
	  	   				alto = "5";
	  	   			}

	   sprite.tipo = (tipoMensaje)atoi(tipo.c_str());
	   sprite.objectId = objectId;
	   sprite.message = ancho+";"+alto;
	   listaSprites.push_back(sprite);
	}
}
void Parser::getxmlVentana(const pugi::xml_document* doc)
{
	pugi::xml_node ventanaNode = doc->child("ventana");
	std::string tipo = ventanaNode.child("tipo").first_child().value();
	std::string objectId = ventanaNode.child("objectId").first_child().value();
	std::string ancho = ventanaNode.child("ancho").first_child().value();
	std::string alto = ventanaNode.child("alto").first_child().value();

	if (!validar(tipo))
		{
			tipo = "19";
		}
	if (!validar(ancho))
		{
			ancho = "800";
		}
	if (!validar(alto))
		{
			alto = "600";
		}

	ventana.tipo = (tipoMensaje)atoi(tipo.c_str());
	ventana.objectId = objectId;
	ventana.message = ancho+"x"+alto;
}
void Parser::getxmlObjetos(const pugi::xml_document* doc)
{
	pugi::xml_node objetosNode = doc->child("objetos");
	std::string tipo = objetosNode.child("tipo").first_child().value();
	   if (!validar(tipo))
	   			{
	   				tipo = "21";
	   			}
	for (pugi::xml_node i = objetosNode.first_child(); i; i = i.next_sibling())
	{
	   mensajeStruct objeto;
	   std::string objectId = i.child("objectId").first_child().value();
	   std::string imagen = i.child("imagen").first_child().value();
	   std::string ancho = i.child("ancho").first_child().value();
	   std::string alto = i.child("alto").first_child().value();
	   if (!validar(ancho))
	   			{
	   				ancho = "200";
	   			}
	   if (!validar(alto))
	  	   		{
	  	   			alto = "200";
	  	   		}

	   objeto.tipo = (tipoMensaje)atoi(tipo.c_str());
	   objeto.objectId = objectId;
	   objeto.message = imagen+";"+ancho+";"+alto;
	   listaObjetos.push_back(objeto);
	}
}
void Parser::getxmlFondos(const pugi::xml_document* doc)
{

fondo capas[] = { {"A",0}, {"B",0}, {"C",0}, {"D",0}, {"E",0}, {"F",0}, {"G",0}, {"H",0}};

	pugi::xml_node fondosNode = doc->child("fondos");
	std::string tipo = fondosNode.child("tipo").first_child().value();
	   if (!validar(tipo))
	   			{
	   				tipo = "21";
	   			}
	for (pugi::xml_node i = fondosNode.first_child(); i; i = i.next_sibling())
	{
	   mensajeStruct fondo;
	   std::string imagen = i.child("imagen").first_child().value();
	   std::string ancho = i.child("ancho").first_child().value();
	   std::string alto = i.child("alto").first_child().value();
	   std::string zIndex = i.child("zIndex").first_child().value();
	   if (!validar(ancho))
	   			{
	   				ancho = "200";
	   			}
	   if (!validar(alto))
	  	   		{
	  	   			alto = "200";
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
	   ss << capas[atoi(zIndex .c_str())-1].numero;
	   fondo.objectId = capas[atoi(zIndex .c_str())-1].letra + ss.str();
	   fondo.tipo = (tipoMensaje)atoi(tipo.c_str());
	   fondo.message = imagen+";"+ancho+";"+alto;
	   listaObjetos.push_back(fondo);
	   capas[atoi(zIndex.c_str())-1].numero = capas[atoi(zIndex.c_str())-1].numero + 1;
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


