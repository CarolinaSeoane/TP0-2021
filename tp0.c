/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"
#include <readline/readline.h>
#include <string.h>

t_paquete* armar_paquete();

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	//char* ip;
	//char* puerto;
	char* valor;


	t_log* logger;

	t_config* config;

	logger = iniciar_logger();

	log_info(logger, "Soy un log");

	config = leer_config();

	valor = config_get_string_value(config, "CLAVE");

	log_info(logger, valor);

	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	conexion = crear_conexion(config_get_string_value(config, "IP"), config_get_string_value(config, "PUERTO"));

	enviar_mensaje(valor, conexion);

	t_paquete* paquete = armar_paquete();

	//paquete(conexion);
	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);

	terminar_programa(conexion, logger, config);
}

t_log* iniciar_logger(void)
{
	return log_create("tp0.log", "tp0", 1, LOG_LEVEL_INFO);
}

t_config* leer_config(void)
{
	return config_create("tp0.config");
}

void leer_consola(t_log* logger)
{
	char* leido;

	leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		log_info(logger, leido);
		free(leido);
		leido = readline(">");
	}

	free(leido);

}

t_paquete* armar_paquete()
{
	t_paquete* paquete = crear_paquete();
	char* leido = readline(">");

	while(strncmp(leido, "", 1) != 0) {
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
		leido = readline(">");
	}

	free(leido);

	return paquete;

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
