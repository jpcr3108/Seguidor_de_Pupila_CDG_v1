#include "registroUsuario.h"
#include "string.h"
//#include "ofXml.h"

//--------------------------------------------------------------
void registroUsuario::setup() {

	yaLei = FALSE;
	Guardar = FALSE;
	Editar = FALSE;
	Inicio = FALSE;
	modo_imagen = FALSE;
	yaTiempo = FALSE;
	bID = TRUE;
	cont_pos = 0; //cambiar si no quiero que se reinice cada vez
	int w = ofGetWidth();
	int h = ofGetHeight();
	ocra.loadFont("fonts/OCRAStd.otf", 8);
	tema_carpeta = new ofxDatGuiThemeCharcoalMod(16);
	tema_input_listbox = new ofxDatGuiThemeCharcoalMod(12);
	tema_boton = new ofxDatGuiThemeCharcoalMod(18);
	/*{ new ofxDatGuiTheme(true),
	new ofxDatGuiThemeSmoke(),
	new ofxDatGuiThemeWireframe(),
	new ofxDatGuiThemeMidnight(),
	new ofxDatGuiThemeAqua(),
	new ofxDatGuiThemeCharcoal(),
	new ofxDatGuiThemeAutumn(),
	new ofxDatGuiThemeCandy() };*/

	//-------instanciacion-------------------------------------------------------------------
	//Folder con datos
	datos_usuario = new ofxDatGuiFolder("Datos Personales", ofColor::antiqueWhite);
	datos_usuario->setLabelUpperCase(FALSE);
	nombre = datos_usuario->addTextInput("Nombre", "Ingrese Nombre");
	datos_usuario->addBreak();
	apellido = datos_usuario->addTextInput("Apellido", "Ingrese Apellido");
	datos_usuario->addBreak();
	edad = datos_usuario->addTextInput("Edad", "Ingrese Edad");
	datos_usuario->addBreak();
	datos_usuario->expand();
	//Folder con Label de datos
	label_datos_usuario = new ofxDatGuiFolder("Datos Personales Ingresados", ofColor::blueViolet);
	label_datos_usuario->setLabelUpperCase(FALSE);
	label_nombre = label_datos_usuario->addLabel("Nombre");
	label_datos_usuario->addBreak();
	label_apellido = label_datos_usuario->addLabel("Apellido");
	label_datos_usuario->addBreak();
	label_edad = label_datos_usuario->addLabel("Edad");
	label_datos_usuario->addBreak();
	label_genero = label_datos_usuario->addLabel("Genero");
	label_datos_usuario->addBreak();
	label_datos_usuario->expand();
	//Listboxes	
	vector<string> generos = {"Masculino", "Femenino"};
	genero = new ofxDatGuiDropdown("Genero", generos);
	vector<string> modos = { "Imagen", "Video", "World" };
	modo_prueba = new ofxDatGuiDropdown("Modo de Prueba", modos);
	//Botones
	boton_guardar=new ofxDatGuiButton("Guardar");
	boton_editar = new ofxDatGuiButton("Editar");
	boton_inicio = new ofxDatGuiButton("Iniciar");
	abrir_archivo = new ofxDatGuiButton("Abrir Archivo");
	//Labels
	ID = new ofxDatGuiLabel("ID");
	ID_mod = new ofxDatGuiLabel("MOD");
	//Input
	tiempo_prueba = new ofxDatGuiTextInput("Tiempo de Prueba", "Ingrese un valor en segundos");
	//-----------------------------------------------------------------------------------------
		
	//------Temas-------------------------------------------------------------------------------
	datos_usuario->setTheme(tema_carpeta);
	label_datos_usuario->setTheme(tema_carpeta);
	nombre->setTheme(tema_input_listbox);
	apellido->setTheme(tema_input_listbox);
	edad->setTheme(tema_input_listbox);
	label_nombre->setTheme(tema_input_listbox);
	label_apellido->setTheme(tema_input_listbox);
	label_edad->setTheme(tema_input_listbox);
	label_genero->setTheme(tema_input_listbox);
	genero->setTheme(tema_input_listbox);
	boton_guardar->setTheme(tema_boton);
	boton_editar->setTheme(tema_boton);
	boton_inicio->setTheme(tema_boton);
	abrir_archivo->setTheme(tema_boton);
	modo_prueba->setTheme(tema_input_listbox);
	ID->setTheme(tema_boton);
	ID_mod->setTheme(tema_boton);
	tiempo_prueba->setTheme(tema_input_listbox);
	//----------------------------------------------------------------------------------
	//--------DIMENSIONES---------------------------------------------------------------
	datos_usuario->setWidth(500, 1);
	label_datos_usuario->setWidth(500, 1);
	nombre->setWidth(500, .33);
	apellido->setWidth(500, .33);
	edad->setWidth(500, .33);
	label_nombre->setWidth(500, .33);
	label_apellido->setWidth(500, .33);
	label_edad->setWidth(500, .33);
	label_genero->setWidth(500, .33);
	genero->setWidth(500, 1);
	boton_guardar->setWidth(500, 1);
	boton_guardar->setHeight(100);
	boton_editar->setWidth(500, 1);
	boton_editar->setHeight(100);
	boton_inicio->setWidth(500, 1);
	boton_inicio->setHeight(100);
	abrir_archivo->setWidth(500, 1);
	abrir_archivo->setHeight(50);
	modo_prueba->setWidth(500, 1);
	ID->setWidth(250, 1);
	ID_mod->setWidth(250, 1);
	tiempo_prueba->setWidth(500, 0.33);
	//----------------------------------------------------------------------------------
	//----------Posicionamiento----------------------------------------------------------------------------
	datos_usuario->setPosition(w / 4 - 250, 50);
	genero->setPosition(datos_usuario->getX(), datos_usuario->getY()+datos_usuario->getHeight());
	boton_guardar->setPosition(datos_usuario->getX(), genero->getY() + genero->getHeight() + 60);
	label_datos_usuario->setPosition(3*w / 4 - 250, 50);
	ID->setPosition(label_datos_usuario->getX(), label_datos_usuario->getY() + label_datos_usuario->getHeight());
	ID_mod->setPosition(label_datos_usuario->getX()+ID->getWidth(), ID->getY() );
	abrir_archivo->setPosition(datos_usuario->getX(), boton_guardar->getY() + boton_guardar->getHeight() + 50);
	tiempo_prueba->setPosition(label_datos_usuario->getX(), abrir_archivo->getY());
	modo_prueba->setPosition(label_datos_usuario->getX(), tiempo_prueba->getY() + tiempo_prueba->getHeight() + 5);
	boton_editar->setPosition(label_datos_usuario->getX(), ID->getY() + ID->getHeight() + 5);
	boton_inicio->setPosition(label_datos_usuario->getX(), abrir_archivo->getY() + abrir_archivo->getHeight() + 150);
	//--------------------------------------------------------------------------------------------------------
	// Apague todo en MAYUSCULAS menos botones----------------------------------------------------------------
	nombre->setTextUpperCase(FALSE);
	apellido->setTextUpperCase(FALSE);
	edad->setTextUpperCase(FALSE);
	nombre->setLabelUpperCase(FALSE);
	apellido->setLabelUpperCase(FALSE);
	edad->setLabelUpperCase(FALSE);
	label_nombre->setLabelUpperCase(FALSE);
	label_apellido->setLabelUpperCase(FALSE);
	label_edad->setLabelUpperCase(FALSE);
	label_genero->setLabelUpperCase(FALSE);
	genero->setLabelUpperCase(FALSE);
	modo_prueba->setLabelUpperCase(FALSE);
	tiempo_prueba->setLabelUpperCase(FALSE);
	//Eventos--------------------------------------------------------------------------------------------------
	boton_guardar->onButtonEvent(this, &registroUsuario::onButtonEvent);
	boton_editar->onButtonEvent(this, &registroUsuario::onButtonEvent);
	boton_inicio->onButtonEvent(this, &registroUsuario::onButtonEvent);
	abrir_archivo->onButtonEvent(this, &registroUsuario::onButtonEvent);
	datos_usuario->onTextInputEvent(this, &registroUsuario::onTextInputEvent);
	genero->onDropdownEvent(this,&registroUsuario::onDropdownEvent);
	modo_prueba->onDropdownEvent(this, &registroUsuario::onDropdownEvent);
	tiempo_prueba->onTextInputEvent(this, &registroUsuario::onTextInputEvent);
}

//--------------------------------------------------------------
void registroUsuario::update() {
	datos_usuario->update();
	label_datos_usuario->update();
	genero->update();
	modo_prueba->update();
	boton_guardar->update();
	boton_editar->update();
	boton_inicio->update();
	abrir_archivo->update();
	ID->update();
	ID_mod->update();	
	tiempo_prueba->update();
}

//--------------------------------------------------------------
void registroUsuario::draw() {
	datos_usuario->draw();
	label_datos_usuario->draw();
	genero->draw();
	modo_prueba->draw();
	boton_guardar->draw();
	boton_editar->draw();
	boton_inicio->draw();
	abrir_archivo->draw();
	ID->draw();
	ID_mod->draw();
	tiempo_prueba->draw();
	if (yaLei) {
		ocra.drawString(path_imagen, label_datos_usuario->getX(), boton_editar->getY() + boton_editar->getHeight() + 20);
	}
	
	
}
//--------------------------------------------------------------

void registroUsuario::onButtonEvent(ofxDatGuiButtonEvent e)
{
	if (e.target->is("Guardar")) {
		cout << "Guardar was clicked" << endl;
		label_nombre->setLabel(nombre->getText());
		label_apellido->setLabel(apellido->getText());
		label_edad->setLabel(edad->getText());
		label_genero->setLabel(genero->getSelected()->getLabel());

		xml_ID.loadFile("settings/ID.xml");
		numeroID = xml_ID.getValue("contador:contador", 0);
		if (bID) {
			numeroID++;
			bID = FALSE;		
		}
		xml_ID.setValue("contador:contador", numeroID);
		xml_ID.saveFile("settings/ID.xml");
		ID_mod->setLabel(std::to_string(numeroID));

		Guardar = TRUE;
		
	}
	else if (e.target->is("Editar")) {
		cout << "Editar was clicked" << endl;
		nombre->setText(label_nombre->getLabel());
		apellido->setText(label_apellido->getLabel());
		edad->setText(label_edad->getLabel());
		Guardar = FALSE;
		Editar = TRUE;
	}
	else if (e.target->is("Iniciar")) {
		cout << "Iniciar was clicked" << endl;
		
		if (xml_datos.tagExists("datos")==FALSE) {
			xml_datos.addTag("datos");
		}
		else {
			xml_datos.loadFile("settings/Datos_Usuarios.xml");
		}
			
		xml_datos.pushTag("datos", 0);
		xml_datos.addTag("usuario");
		xml_datos.setAttribute("usuario", "ID", ID_mod->getLabel(), cont_pos);
		xml_datos.pushTag("usuario", cont_pos);
		xml_datos.addValue("ID", ID_mod->getLabel());
		xml_datos.addValue("Nombre", label_nombre->getLabel());
		xml_datos.addValue("Apellido", label_apellido->getLabel());
		xml_datos.addValue("Edad", label_edad->getLabel());
		xml_datos.addValue("Genero", label_genero->getLabel());
		xml_datos.addValue("Imagen_Vista", path_imagen);
		xml_datos.addValue("Tiempo_prueba", tp);
		xml_datos.popTag();
		xml_datos.popTag();
		xml_datos.saveFile("settings/Datos_Usuarios.xml");
		cont_pos++;

		/*xml_usuario_actual.setValue("usuario:ID", ID_mod->getLabel());
		xml_usuario_actual.setValue("usuario:nombre", label_nombre->getLabel());
		xml_usuario_actual.setValue("usuario:apellido", label_apellido->getLabel());
		xml_usuario_actual.setValue("usuario:edad", label_edad->getLabel());
		xml_usuario_actual.setValue("usuario:genero", label_genero->getLabel());
		xml_usuario_actual.saveFile("settings/usuario_actual.xml");*/

		Inicio = TRUE;
	}
	else if (e.target->is("Abrir Archivo")) {
		ofToggleFullscreen();
		ofFileDialogResult result = ofSystemLoadDialog("Seleccionar Archivo");
		if (result.bSuccess) {
			yaLei = TRUE;
			ofToggleFullscreen();
			path_imagen = result.getPath();
			//abrir_archivo->setLabel(path_imagen);
			// load your file at `path`
		}
	}
	
}
//---------------------------------------------------------------
void registroUsuario::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	//cout << e.target->getText() << endl;
	if (e.target->is("Tiempo de prueba")) {
		tp = e.target->getText();
		if (yaTiempo == FALSE) {
			yaTiempo = TRUE;
		}

	}
	
}
//------------------------------------------------------------------
void registroUsuario::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
	
	if (e.target->is("Genero")) {
		cout << genero->getChildAt(e.child) << endl;
		
	}
	else if (e.target->is("Modo de Prueba")) {
		cout << modo_prueba->getChildAt(e.child) << endl;
		if (e.child == 0) { modo_imagen = TRUE; }
		//if (e.child == 1) {}
		//if (e.child == 2) {}
	}
	
}
//--------------------------------------------------------------
void registroUsuario::keyPressed(int key) {

}

//--------------------------------------------------------------
void registroUsuario::keyReleased(int key) {

}

//--------------------------------------------------------------
void registroUsuario::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void registroUsuario::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void registroUsuario::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void registroUsuario::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void registroUsuario::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void registroUsuario::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void registroUsuario::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void registroUsuario::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void registroUsuario::dragEvent(ofDragInfo dragInfo) {

}

