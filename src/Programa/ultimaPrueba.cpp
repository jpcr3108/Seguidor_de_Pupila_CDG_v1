#include "stdio.h"
#include "ultimaPrueba.h"


void ultimaPrueba::setup() {
	int w = ofGetWidth();
	int h = ofGetHeight();

	tema = new ofxDatGuiThemeCharcoalMod(16);
	tema_label = new ofxDatGuiThemeCharcoalMod(12);
	ocrabig.loadFont("fonts/OCRAStd.otf", 18);
	ocra13.loadFont("fonts/OCRAStd.otf", 13);
	ocra7.loadFont("fonts/OCRAStd.otf", 7);
	ocra8.loadFont("fonts/OCRAStd.otf", 8);
	bEjecucion = true;
	
	Buscar_b = FALSE;

	datos_usuario = new ofxDatGuiFolder("Datos Personales", ofColor::blueViolet);
	datos_usuario->setLabelUpperCase(FALSE);
	label_nombre = datos_usuario->addLabel("Nombre");
	datos_usuario->addBreak();
	label_apellido = datos_usuario->addLabel("Apellido");
	datos_usuario->addBreak();
	label_edad = datos_usuario->addLabel("Edad");
	datos_usuario->addBreak();
	label_genero =datos_usuario->addLabel("Genero");
	datos_usuario->addBreak();
	label_ID = datos_usuario->addLabel("ID");
	datos_usuario->addBreak();
	label_pp = datos_usuario->addLabel("Primer Punto");
	datos_usuario->addBreak();
	label_pmv = datos_usuario->addLabel("Punto + Visto");
	datos_usuario->addBreak();
	datos_usuario->expand();

	buscador = new ofxDatGuiFolder("Buscador", ofColor::blueViolet);
	buscador->setLabelUpperCase(FALSE);
	input_ID=buscador->addTextInput("ID", "Buscar por ID");
	buscador->addBreak();
	buscar = buscador->addButton("Buscar");
	buscador->expand();

	flecha_izq =new ofxDatGuiButton("Atras");
	flecha_der = new ofxDatGuiButton("Adelante");
	

	//------Temas-------------------------------------------------------------------------------
	datos_usuario->setTheme(tema);
	label_nombre->setTheme(tema_label);
	label_apellido->setTheme(tema_label);
	label_edad->setTheme(tema_label);
	label_genero->setTheme(tema_label);
	label_ID->setTheme(tema_label);
	label_pp->setTheme(tema_label);
	label_pmv->setTheme(tema_label);
	buscador->setTheme(tema);
	buscar->setTheme(tema);
	flecha_izq->setTheme(tema_label);
	flecha_der->setTheme(tema_label);
	input_ID->setTheme(tema_label);	
	//----------------------------------------------------------------------------------
	//--------DIMENSIONES---------------------------------------------------------------
	datos_usuario->setWidth(300, 1);
	label_nombre->setWidth(300, .33);
	label_apellido->setWidth(300, .33);
	label_edad->setWidth(300, .33);
	label_genero->setWidth(300, .33);
	label_ID->setWidth(300, .33);
	label_pp->setWidth(300, .33);
	label_pmv->setWidth(300, .33);
	buscador->setWidth(300, 1);
	input_ID->setWidth(300, 0.20);
	buscar->setWidth(300, 1);
	buscar->setHeight(100);
	flecha_izq->setWidth(148, 1);
	flecha_izq->setHeight(50);
	flecha_der->setWidth(148, 1);
	flecha_der->setHeight(50);
	//----------------------------------------------------------------------------------
	//----------Posicionamiento----------------------------------------------------------------------------
	datos_usuario->setPosition(w- 300, 80);
	buscador->setPosition(datos_usuario->getX(), datos_usuario->getY() + datos_usuario->getHeight() + 100);
	flecha_izq->setPosition(datos_usuario->getX(), buscador->getY() + buscador->getHeight() + 5);
	flecha_der->setPosition(flecha_izq->getX()+flecha_izq->getWidth()+4, flecha_izq->getY());
	//--------------------------------------------------------------------------------------------------------
	// Apague todo en MAYUSCULAS menos botones----------------------------------------------------------------
	label_nombre->setLabelUpperCase(FALSE);
	label_apellido->setLabelUpperCase(FALSE);
	label_edad->setLabelUpperCase(FALSE);
	label_genero->setLabelUpperCase(FALSE);
	label_ID->setLabelUpperCase(FALSE);
	label_pp->setLabelUpperCase(FALSE);
	label_pmv->setLabelUpperCase(FALSE);
	input_ID->setLabelUpperCase(FALSE);
	//Eventos--------------------------------------------------------------------------------------------------
	buscar->onButtonEvent(this, &ultimaPrueba::onButtonEvent);
	flecha_izq->onButtonEvent(this, &ultimaPrueba::onButtonEvent);
	flecha_der->onButtonEvent(this, &ultimaPrueba::onButtonEvent);
	buscador->onTextInputEvent(this, &ultimaPrueba::onTextInputEvent);
}

void ultimaPrueba::update() {
	datos_usuario->update();
	buscador->update();
	flecha_der->update();
	flecha_izq->update();

}

void ultimaPrueba::draw() {
	if(bEjecucion){

		xml_datos_usuario.loadFile("settings/Datos_Usuarios.xml");
		xml_datos_usuario.pushTag("datos", 0);
		size_xml = xml_datos_usuario.getNumTags("usuario");
		cout << size_xml << endl;
		xml_datos_usuario.pushTag("usuario", cont_pos);
		label_ID->setLabel("ID: "+std::to_string(xml_datos_usuario.getValue("ID", 0)));
		label_nombre->setLabel("Nombre: " + xml_datos_usuario.getValue("Nombre", ""));
		label_apellido->setLabel("Apellido: " + xml_datos_usuario.getValue("Apellido", ""));
		label_edad->setLabel("Edad: " + std::to_string(xml_datos_usuario.getValue("Edad", 0)));
		label_genero->setLabel("Genero: " + xml_datos_usuario.getValue("Genero", ""));
		label_pp->setLabel("Primer punto: " + std::to_string(xml_datos_usuario.getValue("Primer_punto_X", 0)) + " , " + std::to_string(xml_datos_usuario.getValue("Primer_punto_Y", 0)));
		label_pmv->setLabel("Punto mas visto: " + std::to_string(xml_datos_usuario.getValue("Punto_Mas_Visto_X", 0)) + " , " + std::to_string(xml_datos_usuario.getValue("Punto_Mas_Visto_Y", 0)));
		imagen.load(xml_datos_usuario.getValue("Imagen_Resultado",""));
		xml_datos_usuario.popTag();
		xml_datos_usuario.pushTag("usuario", 0);
		primerID = xml_datos_usuario.getValue("ID",0);
		xml_datos_usuario.popTag();
		xml_datos_usuario.pushTag("usuario", size_xml-1);
		ultimoID = xml_datos_usuario.getValue("ID", 0);
		xml_datos_usuario.popTag();
		xml_datos_usuario.popTag();

		bEjecucion = FALSE;
	}
	if (Buscar_b) {
			ocra13.drawString("Error en la busqueda", datos_usuario->getX(), flecha_izq->getY() + flecha_izq->getHeight() + 50);
			ocra13.drawString("Revise su ID", datos_usuario->getX(), flecha_izq->getY() + flecha_izq->getHeight() + 80);
	}
					
	flecha_der->draw();
	flecha_izq->draw();
	imagen.draw(10, 80, ofGetWidth()-320, ofGetHeight()-100);
	datos_usuario->draw();
	buscador->draw();	
	ofSetColor(255, 255, 255);
	ocrabig.drawString("Prueba # "+label_ID->getLabel(), ofGetWidth() / 2 - 130, 40);

	
}

void ultimaPrueba::onButtonEvent(ofxDatGuiButtonEvent e) {
	
	if (e.target->is("Buscar")) {
		cout << "Buscar was clicked" << endl;
		
		string lectura = input_ID->getText();
		char lect[15];
		strcpy(lect, lectura.c_str());
		int int_lectura = atoi(lect);
		Busqueda(int_lectura);
		
	}
	else if (e.target->is("Atras")) {
		cout << primerID << endl;
		string lectura = label_ID->getLabel();
		char lect[15];
		strcpy(lect, lectura.c_str());
		int int_lectura = atoi(lect)-1;
		if (int_lectura < primerID) {
			int_lectura = ultimoID;
		}
		Busqueda(int_lectura);
						
	}
	else if (e.target->is("Adelante")) {
		cout << ultimoID << endl;
		string lectura = label_ID->getLabel();
		char lect[15];
		strcpy(lect, lectura.c_str());
		int int_lectura = atoi(lect) + 1;
		if (int_lectura > ultimoID) {
			int_lectura = primerID;
		}
		Busqueda(int_lectura);
	}
}

void ultimaPrueba::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	//cout << e.target->getText() << endl;
	
}
void ultimaPrueba::keyPressed(int key) {

}

//--------------------------------------------------------------
void ultimaPrueba::keyReleased(int key) {

}

//---------------------------p-----------------------------------
void ultimaPrueba::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ultimaPrueba::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ultimaPrueba::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ultimaPrueba::mouseReleased(int x, int y, int button) {

}

void ultimaPrueba::Busqueda(int id) {
	xml_datos_usuario.loadFile("settings/Datos_Usuarios.xml");
	xml_datos_usuario.pushTag("datos", 0);
	int size = xml_datos_usuario.getNumTags("usuario");

	if (primerID<=id && id<=ultimoID) {
		Buscar_b = FALSE;
		for (int i = 0; i <size; i++) {

			xml_datos_usuario.pushTag("usuario", i);

			if (id == xml_datos_usuario.getValue("ID", 0)) {
				label_ID->setLabel(std::to_string(xml_datos_usuario.getValue("ID", 0)));
				label_nombre->setLabel(xml_datos_usuario.getValue("Nombre", ""));
				label_apellido->setLabel(xml_datos_usuario.getValue("Apellido", ""));
				label_edad->setLabel(std::to_string(xml_datos_usuario.getValue("Edad", 0)));
				label_genero->setLabel(xml_datos_usuario.getValue("Genero", ""));
				label_pp->setLabel(std::to_string(xml_datos_usuario.getValue("Primer_punto_X", 0)) + " , " + std::to_string(xml_datos_usuario.getValue("Primer_punto_Y", 0)));
				label_pmv->setLabel(std::to_string(xml_datos_usuario.getValue("Punto_Mas_Visto_X", 0)) + " , " + std::to_string(xml_datos_usuario.getValue("Punto_Mas_Visto_Y", 0)));
				imagen.load(xml_datos_usuario.getValue("Imagen_Resultado", ""));
				xml_datos_usuario.popTag();
				i = size;
			}
			else {
				xml_datos_usuario.popTag();
			}
		}
		xml_datos_usuario.popTag();


	}
	else {
		Buscar_b = TRUE;
	}


}