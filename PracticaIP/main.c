#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>

#define MAXNOMBRE 21 //Sumado +1 caracter nulo
#define MAXAPELLIDO 51 //Sumado +1 caracter nulo
#define MAXDNI 10 //Sumado +1 caracter nulo
#define MAXCHARUSUARIO 10 //Sumado +1 caracter nulo
#define MAXPERFIL 6 //Sumado +1 caracter nulo
#define MAXTITULO 51 //Sumado +1 caracter nulo
#define MAXAMBITO 21 //Sumado +1 caracter nulo
#define MAXGENERO 21 //Sumado +1 caracter nulo
#define MAXFECHA 11 //Sumado +1 caracter nulo
#define MAXUSUARIOS 50 //Numero maximo de usuarios
#define MAXRECURSOS 70 //Numero maximo de usuarios
#define MAXREPRODUCCIONES 80 //Numero maximo de usuarios

//usuario
typedef struct {
    char nombre[MAXNOMBRE/*+1*/];
    char apellidos[MAXAPELLIDO/*+1*/];
    char dni[MAXDNI/*+1*/];
    char usuarioURJC[MAXCHARUSUARIO/*+1*/];
    float saldo;
    char perfil[MAXPERFIL/*+1*/];
} tipoUsuario;

// recursos
typedef struct {
    int id;
    char titulo[MAXTITULO/*+1*/];
    char ambito[MAXAMBITO/*+1*/];
    char genero [MAXGENERO/*+1*/];
    float coste;
    int duracion;
} tipoRecurso;
// reproducciones
typedef struct {
    char fecha[MAXFECHA/*+1*/];
    char usuarioURJC[MAXCHARUSUARIO/*+1*/];
    int id;
} tipoReproduccion;
// listado usuarios
typedef struct {
    tipoUsuario listaUsuarios[MAXUSUARIOS];
    int tope;
} tipoListaUsuarios;
// listado recursos
typedef struct {
    tipoRecurso listaRecursos[MAXRECURSOS];
    int tope;
} tipoListaRecursos;
// listado reproducciones
typedef struct {
    tipoReproduccion listaReproduccion[MAXREPRODUCCIONES];
    int tope;
} tipoListaReproducciones;

void menu();
void mostrarUsuario (tipoUsuario usuario);
void mostrarListadoUsuariosURJC(tipoListaUsuarios lista);
void mostrarRecurso (tipoRecurso recurso);
void mostrarListadoRecursos(tipoListaRecursos lista);
void mostrarReproduccion(tipoReproduccion reproduccion);
void mostrarListadoReproducciones(tipoListaReproducciones lista);
void leerUsuario (tipoUsuario *nuevoUsuario);
int buscarUsuarioURJC (tipoListaUsuarios lista, char UsuarioURJC[MAXCHARUSUARIO]);
void altaUsuario (tipoListaUsuarios *lista, tipoUsuario nuevo);
void borrarReproducciones (tipoListaReproducciones *lista, tipoReproduccion eliminado);
void bajaUsuario (tipoListaUsuarios *lista, tipoUsuario eliminado,tipoListaReproducciones *lista2);
int generarIDRecuso(tipoListaRecursos lista);
void leerRecurso (tipoRecurso *nuevoRecurso,tipoListaRecursos lista);
int buscarRecursoURJC (tipoListaRecursos lista, int id );
void altaRecurso (tipoListaRecursos *lista, tipoRecurso nuevo);
void bajaRecurso (tipoListaRecursos *lista, tipoRecurso eliminado,tipoListaReproducciones listaReproducciones);
int buscarReproduccionURJC (tipoListaReproducciones lista, char usuarioURJC[MAXCHARUSUARIO]);
int buscarReproduccionID (tipoListaReproducciones lista, int id);
void reproduccionRecursoMultimedia (int posicionUsuario, int posicionRecurso, tipoListaRecursos *listaRecursos, tipoListaUsuarios *listaUsuarios, tipoListaReproducciones *listaReproducciones );
void guardarUsuarios(FILE *punteroFichero, tipoListaUsuarios listaDeUsuarios);
void guardarRecursos(FILE *punteroFichero,tipoListaRecursos listaDeRecursos );
void guardarReproducciones(FILE *punteroFichero,tipoListaReproducciones listaDeReproducciones);
void cargarUsuarios(FILE *punteroFichero,tipoListaUsuarios *listaDeUsuarios);
void cargarRecursos(FILE *punteroFichero,tipoListaRecursos *listaDeRecursos );
void cargarReproducciones(FILE *punteroFichero,tipoListaReproducciones *listaDeReproducciones);
int contadorReproducciones(tipoListaReproducciones lista, char usuarioURJC[MAXNOMBRE]);
void relojArena();
void generarInformeUsuarios(FILE *punteroFichero,tipoListaUsuarios listaUsuarios, tipoListaReproducciones listaReproducciones);
void ordenarUsuariosAlfabeticamente(tipoListaUsuarios *lista);
void ordenarId(tipoListaRecursos *lista);
void ordenarPorFecha(tipoListaReproducciones *lista);
int main() {
    int random;
    char opcion;
    char usuarioURJC[MAXCHARUSUARIO];
    int idRecurso;
    FILE *pFichero;
    tipoUsuario usuario;
    tipoRecurso recurso;
    tipoReproduccion reproduccion;
    tipoListaUsuarios listaUsuarios;
    tipoListaRecursos listaRecursos;
    tipoListaReproducciones listaReproducciones;
    listaUsuarios.tope=0;
    listaRecursos.tope=0;
    listaReproducciones.tope=0;
    do{
        fflush(stdin);
        menu();
        scanf("%c",&opcion);
        switch (opcion){
            case 'A':
	     	 case 'a':
                printf("Alta usuario\n");
                leerUsuario(&usuario);
                altaUsuario(&listaUsuarios, usuario);
                mostrarListadoUsuariosURJC(listaUsuarios);
                break;
            case 'B':
                case 'b':
                printf("Baja usuario\n");
                printf("Introduzca el usuario URJC del usuario que quiere eliminar\n");
                scanf("%s",usuario.usuarioURJC);
                buscarUsuarioURJC(listaUsuarios, usuario.usuarioURJC);
                bajaUsuario(&listaUsuarios, usuario,&listaReproducciones);
                mostrarListadoUsuariosURJC(listaUsuarios);
                break;
		case 'C':
            case 'c':
                printf("Alta recurso multimedia\n");
                leerRecurso(&recurso,listaRecursos);
                altaRecurso(&listaRecursos, recurso);
                mostrarListadoRecursos(listaRecursos);
                break;
            case 'd':
		case 'D':
                printf("Baja recurso multimedia\n");
                bajaRecurso(&listaRecursos, recurso,listaReproducciones);
                mostrarListadoRecursos(listaRecursos);
                break;
            case 'E':
		 case 'e':
                printf("Listado usuarios\n");
                mostrarListadoUsuariosURJC(listaUsuarios);
                break;
            case 'F':
		case 'f':
                printf("Listado recursos multimedia\n");
                mostrarListadoRecursos(listaRecursos);
                break;
        case 'G':
            case 'g':
                printf("Listado reproducciones\n");
                mostrarListadoReproducciones(listaReproducciones);
                break;
            case 'H':
            case 'h':
                printf("Reproduccion de un recurso multimedia por un usuario\n");
                do{
                    printf("Introduzca el nombre de un usuarioURJC:");
                    scanf("%s",usuarioURJC);
                }while (buscarUsuarioURJC(listaUsuarios,usuarioURJC) == -1);
                do{
                    printf("Introduzca el id del recurso a reproducir:");
                    scanf("%d",&idRecurso);
                }while (buscarRecursoURJC(listaRecursos,idRecurso) == -1);
                reproduccionRecursoMultimedia(buscarUsuarioURJC(listaUsuarios, usuarioURJC), buscarRecursoURJC(listaRecursos,idRecurso),&listaRecursos,&listaUsuarios,&listaReproducciones);
                mostrarListadoReproducciones(listaReproducciones);
                mostrarListadoUsuariosURJC(listaUsuarios);
                mostrarListadoRecursos(listaRecursos);
                break;
		 case 'I':
            case 'i':
                printf("Guardar usuarios\n");
                if (listaUsuarios.tope==0){
                    printf("No hay usuarios que guardar, la lista esta vacia");
                }else{
                    guardarUsuarios(pFichero,listaUsuarios);
                }
                break;
		 case 'J':
            case 'j':
                printf("Guardar recursos multimedia\n");
                if (listaRecursos.tope == 0){
                    printf("No hay recursos que guardar, la lista esta vacia");
                }else{
                    guardarRecursos(pFichero, listaRecursos);
                }
                break;
		 case 'K':
            case 'k':
                printf("Guardar reproducciones\n");
                if(listaReproducciones.tope == 0){
                    printf("No hay reproducciones que guardar, la lista esta vacia");
                }else{
                    guardarReproducciones(pFichero, listaReproducciones);
                }
                break;
		case 'L':
            case 'l':
                printf("Cargar usuarios\n");
                cargarUsuarios(pFichero,&listaUsuarios);
                break;
		case 'M':
            case 'm':
                printf("Cargar recursos multimedia\n");
                cargarRecursos(pFichero,&listaRecursos);
                break;
		case 'N':
            case 'n':
                printf("Cargar reproducciones\n");
                cargarReproducciones(pFichero,&listaReproducciones);
                break;
		case 'O':
            case 'o':
                printf("Generar informe de usuarios en archivo\n");
                if(listaUsuarios.tope == 0){
                    printf("No se puede generar informa de usuarios ya que la lista de usuarios esta vacia");
                }else{
                    generarInformeUsuarios(pFichero, listaUsuarios, listaReproducciones);
                }
                break;
		case 'P':
            case 'p':
                printf("Fin del programa\n");
                break;
            default:
                printf("\nOpcion incorrecta\n");
        }

    }while(opcion!='p');
    return 0;
}

void menu(){
    printf("\nElija una opcion: ");
    printf("\na) Alta usuario");
    printf("\nb) Baja usuario");
    printf("\nc) Alta recurso multimedia");
    printf("\nd) Baja recurso multimedia");
    printf("\ne) Listado usuarios");
    printf("\nf) Listado recursos multimedia");
    printf("\ng) Listado reproducciones");
    printf("\nh) Reproduccion de un recurso multimedia por un usuario");
    printf("\ni) Guardar usuarios");
    printf("\nj) Guardar recursos multimedia");
    printf("\nk) Guardar reproducciones");
    printf("\nl) Cargar usuarios");
    printf("\nm) Cargar recursos multimedia");
    printf("\nn) Cargar reproducciones");
    printf("\no) Generar informe de usuarios en archivo");
    printf("\np) Salir\n");
}

void mostrarUsuario (tipoUsuario usuario){
    printf("\nNombre: %s", usuario.nombre);
    printf("\nApellidos: %s", usuario.apellidos);
    printf("\nDNI: %s", usuario.dni);
    printf("\nUsuario URJC: %s", usuario.usuarioURJC);
    printf("\nSaldo: %.2f", usuario.saldo);
    printf("\nPerfil: %s", usuario.perfil);
}

void mostrarListadoUsuariosURJC(tipoListaUsuarios lista) {
    int i;
    printf("Usuarios URJC\n");
    if (lista.tope <= 0) {
        printf("La lista esta vacia\n");
    } else {
        ordenarUsuariosAlfabeticamente(&lista);
        for (i = 0; i < lista.tope; i++) {
            printf("Usuario numero %d",i+1);
            mostrarUsuario(lista.listaUsuarios[i]);
        }
    }
}
void mostrarRecurso (tipoRecurso recurso){
    printf("\nId: %d", recurso.id);
    printf("\nTitulo: %s", recurso.titulo);
    printf("\nAmbito: %s", recurso.ambito);
    printf("\nGenero: %s", recurso.genero);
    printf("\nCoste: %.2f", recurso.coste);
    printf("\nDuracion: %d", recurso.duracion);
}
void mostrarListadoRecursos(tipoListaRecursos lista){
    int i;
    printf("Multimedia URJCTV \n");
    if(lista.tope<=0){
        printf("La lista esta vacía \n");
    }else{
        ordenarId(&lista);
        for(i = 0;i<lista.tope;i++){
            mostrarRecurso (lista.listaRecursos[i]);
        }
    }
}
void mostrarReproduccion(tipoReproduccion reproduccion){
    printf("\nFecha: %s",reproduccion.fecha);
    printf("\nUsuario: %s",reproduccion.usuarioURJC);
    printf("\nID: %d",reproduccion.id);
}
void mostrarListadoReproducciones(tipoListaReproducciones lista){
    int i;
    printf("\n reproducciones \n");
    if(lista.tope<=0){
        printf("\n lista vacia \n");
    }else{
        ordenarPorFecha(&lista);
        for(i = 0;i<lista.tope;i++){
            printf("\n Reproduccion numero %d:   ",i+1);
            mostrarReproduccion(lista.listaReproduccion[i]);
        }
    }
}

void leerUsuario (tipoUsuario *nuevoUsuario){
    printf("Nombre del usuario:");
    scanf("%s",nuevoUsuario->nombre);
    printf("Apellidos del usuario:");
    scanf("%s",nuevoUsuario->apellidos);
    do {
        printf("DNI del usuario:");
        scanf("%s",nuevoUsuario->dni);
        printf("%s\n",nuevoUsuario->dni);
    }while(strlen(nuevoUsuario->dni) != MAXDNI-1);
    printf("Usuario URJC:");
    scanf("%s",nuevoUsuario->usuarioURJC);
    nuevoUsuario->saldo=1000;
    printf("Elija el perfil del usuario (ALU/PDI/PTGAS/PPI): ");
    scanf(" %s",nuevoUsuario->perfil);
}

int buscarUsuarioURJC (tipoListaUsuarios lista, char usuarioURJC[MAXCHARUSUARIO]) {
    int i;
    i = 0;
    while ((i < lista.tope) && (strcmp(usuarioURJC, lista.listaUsuarios[i].usuarioURJC) != 0)) {
        i++;
    }
    if (i >= lista.tope) {
        i = -1;
    }
    return i;
}

void altaUsuario (tipoListaUsuarios *lista, tipoUsuario nuevo){
    int posicion;
    if(lista->tope>=MAXUSUARIOS){
        printf("La lista de usuarios esta llena, no se puede anyadir el usuario\n");
    }
    else{
        posicion= buscarUsuarioURJC(*lista, nuevo.usuarioURJC);
        if(posicion == -1){
            lista->listaUsuarios[lista->tope]=nuevo;
            lista->tope++;
            printf("Usuario anyadido con exito\n\n");
        }
        else{
            printf("Ya hay un usuario con el mismo UsuarioURJC, no se puede anyadir\n");
        }
    }
}
void borrarReproducciones (tipoListaReproducciones *lista, tipoReproduccion eliminado){
    int pos,j;
    do {
        pos = buscarReproduccionURJC(*lista, eliminado.usuarioURJC);
        if (pos == -1){
            printf("No hay reproducciones de dicho usuario");
        }else{
            for (j = pos; j < lista->tope; j++) {
                lista->listaReproduccion[j] = lista->listaReproduccion[j + 1];
            }
            lista->tope--;
            printf("Las reproducciones del usuario han sido eliminadas\n");
        }
    } while (pos!=-1);
}
void bajaUsuario (tipoListaUsuarios *lista, tipoUsuario eliminado,tipoListaReproducciones *lista2) {
    int posicion;
    tipoReproduccion eliminadas;
    int i;
    posicion = buscarUsuarioURJC(*lista, eliminado.usuarioURJC);
    if (posicion == -1) {
        printf("El usuario no esta en la lista\n");
    } else {
        for (i = posicion; i < lista->tope; i++) {
            lista->listaUsuarios[i] = lista->listaUsuarios[i + 1];
        }
        lista->tope--;
        printf("Usuario eliminado\n");
    }
    strcpy(eliminadas.usuarioURJC,eliminado.usuarioURJC);
    borrarReproducciones(lista2,eliminadas);
}
int generarIDRecuso(tipoListaRecursos lista){
    srand(time(NULL));
    int i = 0;
    int id;
    id= rand()%81;
    do {
        if (id == lista.listaRecursos[i].id){
            id = rand()%81;
            i=0;
        }else{
            i++;
        }
    }while (i< lista.tope);
    return id;
}
void leerRecurso (tipoRecurso *nuevoRecurso,tipoListaRecursos lista){
    nuevoRecurso->id = generarIDRecuso(lista);
    do {
        printf("Titulo de la cancion:");
        scanf("%s", nuevoRecurso->titulo);
    }while(sizeof(nuevoRecurso->titulo)>MAXTITULO);
    do{
        printf("Ambito (formacion, cultura o entretenimiento):");
        scanf("%s", nuevoRecurso->ambito);
    }while(sizeof(nuevoRecurso->ambito)>MAXAMBITO);
    do{
        printf("Genero (documental, formativo, accion, ciencia ficcion, drama, comedia, belicas, romantica, terror, animacion, historica o suspense):");
        scanf("%s", nuevoRecurso->genero);
    }while(sizeof(nuevoRecurso->genero)>MAXGENERO);
    do{
        printf("Coste:");
        scanf("%f", &(nuevoRecurso->coste));
    }while (nuevoRecurso->coste < 0);
    do{
        printf("Duracion (en minutos):");
        scanf("%d", &nuevoRecurso->duracion);
    }while (&nuevoRecurso->duracion < 0);

}
int buscarRecursoURJC (tipoListaRecursos lista, int id ) {
    int i;
    i = 0;
    while ((i <= lista.tope) && (id != lista.listaRecursos[i].id)){
        i++;
    }
    if (i >= lista.tope) {
        i = -1;
    }
    return i;
}

void altaRecurso (tipoListaRecursos *lista, tipoRecurso nuevo){
    int posicion;
    if(lista->tope>=MAXRECURSOS){
        printf("La lista de canciones esta llena, no se puede aÃ±adir el recurso\n");
    }
    else{
        posicion= buscarRecursoURJC(*lista, nuevo.id);
        if(posicion == -1){
            lista->listaRecursos[lista->tope]=nuevo;
            lista->tope++;
            printf("Recurso anyadido con exito\n");
        }
        else{
            printf("El recurso ya fue añadido, no se puede anyadir\n");
        }
    }
}
void bajaRecurso (tipoListaRecursos *lista, tipoRecurso eliminado,tipoListaReproducciones listaReproducciones){
    int posicion;
    int i;
    posicion = buscarRecursoURJC(*lista, eliminado.id);
    if (posicion==-1){
        printf("El recurso no esta en la lista\n");
    }
    else{
        if(buscarReproduccionID(listaReproducciones,eliminado.id) == -1){
            for (i=posicion;i<lista->tope;i++){
                lista->listaRecursos[i]=lista->listaRecursos[i+1];
            }
            lista->tope--;
            printf("Recurso eliminado\n");
        }else{
            printf("El recurso ha sido reproducido, no puede eliminarse\n");
        }
    }
}
int buscarReproduccionURJC (tipoListaReproducciones lista, char usuarioURJC[MAXCHARUSUARIO]) {
    int i;
    i = 0;
    while ((i < lista.tope) && (strcmp(usuarioURJC, lista.listaReproduccion[i].usuarioURJC) != 0)) {
        i++;
    }
    if (i >= lista.tope) {
        i = -1;
    }
    return i;
}
int buscarReproduccionID (tipoListaReproducciones lista, int id) {
    int i;
    i = 0;
    while ((i < lista.tope) && (id != lista.listaReproduccion[i].id)){
        i++;
    }
    if (i >= lista.tope) {
        i = -1;
    }
    return i;
}
void reproduccionRecursoMultimedia (int posicionUsuario, int posicionRecurso, tipoListaRecursos *listaRecursos, tipoListaUsuarios *listaUsuarios, tipoListaReproducciones *listaReproducciones ){
    if (listaReproducciones->tope == MAXREPRODUCCIONES){
        printf("No se pueden realizar mas reproducciones, la lista esta llena");
    }else{
        if (listaUsuarios->listaUsuarios[posicionUsuario].saldo >= listaRecursos->listaRecursos[posicionRecurso].coste){
            listaUsuarios->listaUsuarios[posicionUsuario].saldo = listaUsuarios->listaUsuarios[posicionUsuario].saldo - listaRecursos->listaRecursos[posicionRecurso].coste ;
            listaReproducciones->tope ++;
            strcpy(listaReproducciones->listaReproduccion[listaReproducciones->tope-1].usuarioURJC,listaUsuarios->listaUsuarios[posicionUsuario].usuarioURJC);
            listaReproducciones->listaReproduccion[listaReproducciones->tope-1].id = listaRecursos->listaRecursos[posicionRecurso].id;
            //listaReproducciones->listaReproduccion[listaReproducciones->tope-1].fecha = generarFecha();
            printf("Se ha anyadido una reproduccion ");
        }else{
            printf("El usuario no tiene suficiente credito");
        }


    }
}
void guardarUsuarios(FILE *punteroFichero, tipoListaUsuarios listaDeUsuarios){
    char ruta [MAXNOMBRE];
    int i, fwControl;
    printf("\nIntroduzca la ruta del fichero");
    scanf("%s", ruta);
    punteroFichero= fopen(ruta, "w");
    if (punteroFichero != NULL) {
        printf("\nEl fichero se ha abierto correctamente.\n");
        for (i = 0; i< listaDeUsuarios.tope; i++) {
            fwrite(&listaDeUsuarios.listaUsuarios[i], sizeof(listaDeUsuarios.listaUsuarios[i]), 1,
                   punteroFichero );
        }
        fwControl= fclose(punteroFichero);
        if (fwControl != 0) {
            printf("El fichero de escritura ha dado un error en el cierre.\n");
        } else {
            printf("El fichero de escritura se ha cerrado correctamente.\n");
        }
    }
}

void guardarRecursos(FILE *punteroFichero,tipoListaRecursos listaDeRecursos ){
    char ruta [MAXNOMBRE];
    int i, fwControl;
    printf("\nIntroduzca la ruta del fichero");
    scanf("%s", ruta);
    punteroFichero= fopen(ruta, "w");
    if (punteroFichero != NULL) {
        printf("\nEl fichero se ha abierto correctamente.\n");
        for (i = 0; i< listaDeRecursos.tope; i++) {
            fwrite(&listaDeRecursos.listaRecursos[i], sizeof(listaDeRecursos.listaRecursos[i]), 1,punteroFichero );
        }
        fwControl= fclose(punteroFichero);
        if (fwControl != 0) {
            printf("El fichero de escritura ha dado un error en el cierre.\n");
        } else {
            printf("El fichero de escritura se ha cerrado correctamente.\n");
        }
    }
}

void guardarReproducciones(FILE *punteroFichero,tipoListaReproducciones listaDeReproducciones){
    char ruta [MAXNOMBRE];
    int i, fwControl;
    printf("\nIntroduzca la ruta del fichero");
    scanf("%s", ruta);
    punteroFichero= fopen(ruta, "w");
    if (punteroFichero != NULL) {
        printf("\nEl fichero se ha abierto correctamente.\n");
        for (i = 0; i< listaDeReproducciones.tope; i++) {
            fwrite(&listaDeReproducciones.listaReproduccion[i],sizeof(listaDeReproducciones.listaReproduccion[i]), 1,punteroFichero );
        }
        fwControl= fclose(punteroFichero);
        if (fwControl != 0) {
            printf("El fichero de escritura ha dado un error en el cierre.\n");
        } else {
            printf("El fichero de escritura se ha cerrado correctamente.\n");
        }
    }
}

void cargarUsuarios(FILE *punteroFichero,tipoListaUsuarios *listaDeUsuarios){
   char ruta [MAXNOMBRE];
   int i, fwControl, resultado;
   tipoUsuario usuario;
   printf("\nIntroduzca la ruta del fichero");
   scanf("%s", ruta);
   punteroFichero = fopen(ruta, "r");
   if (punteroFichero != NULL){
       printf("\nEl fichero se ha abierto correctamente.\n");
       while ( feof(punteroFichero) == 0){
           resultado = fread(&usuario, sizeof(tipoUsuario), 1, punteroFichero);
           if (resultado == 1){
              altaUsuario( listaDeUsuarios, usuario);
           }
       }
       if (ferror(punteroFichero) != 0){
           printf("\nHa ocurrido algun error en la lectura de contactos.\n");
       } else {
           printf("\nLa lectura de contactos ha tenido exito.\n");
       }
       fwControl = fclose(punteroFichero);
       if (fwControl != 0){
           printf("El fichero de escritura ha dado un error en el cierre.\n");
       } else {
           printf("El fichero de escritura se ha cerrado correctamente.\n");
       }
   }
}
void cargarRecursos(FILE *punteroFichero,tipoListaRecursos *listaDeRecursos ){
    char ruta [MAXNOMBRE];
    int i, fwControl, resultado;
    tipoRecurso recurso;
    printf("\nIntroduzca la ruta del fichero");
    scanf("%s", ruta);
    punteroFichero = fopen(ruta, "r");
    if (punteroFichero != NULL){
        printf("\nEl fichero se ha abierto correctamente.\n");
        while ( feof(punteroFichero) == 0){
            resultado = fread(&recurso, sizeof(tipoRecurso ), 1, punteroFichero);
            if (resultado == 1){
                altaRecurso( listaDeRecursos, recurso);
            }
        }
        if (ferror(punteroFichero) != 0){
            printf("\nHa ocurrido algun error en la lectura de contactos.\n");
        } else {
            printf("\nLa lectura de contactos ha tenido exito.\n");
        }
        fwControl = fclose(punteroFichero);
        if (fwControl != 0){
            printf("El fichero de escritura ha dado un error en el cierre.\n");
        } else {
            printf("El fichero de escritura se ha cerrado correctamente.\n");
        }
    }
}
void cargarReproducciones(FILE *punteroFichero,tipoListaReproducciones *listaDeReproducciones){
    char ruta [MAXNOMBRE];
    int i, fwControl, resultado;
    tipoReproduccion reproduccion;
    printf("\nIntroduzca la ruta del fichero");
    scanf("%s", ruta);
    punteroFichero = fopen(ruta, "r");
    if (punteroFichero != NULL){
        printf("\nEl fichero se ha abierto correctamente.\n");
        while ( feof(punteroFichero) == 0){
            resultado = fread(&reproduccion, sizeof(tipoReproduccion ), 1, punteroFichero);
            if (resultado == 1){
               // altaReproduccion( listaDeReproducciones, reproduccion);
            }
        }
        if (ferror(punteroFichero) != 0){
            printf("\nHa ocurrido algun error en la lectura de contactos.\n");
        } else {
            printf("\nLa lectura de contactos ha tenido exito.\n");
        }
        fwControl = fclose(punteroFichero);
        if (fwControl != 0){
            printf("El fichero de escritura ha dado un error en el cierre.\n");
        } else {
            printf("El fichero de escritura se ha cerrado correctamente.\n");
        }
    }
}
int contadorReproducciones(tipoListaReproducciones lista, char usuarioURJC[MAXNOMBRE]){
    int contador =0;
    for (int i=0; i<=lista.tope; i++){
        if (strcmp(usuarioURJC,lista.listaReproduccion[i].usuarioURJC)){
            i++;
        }
    }
    return contador;
};
void relojArena(){
    // 3 segundos de espera...
    sleep(3);
}
void generarInformeUsuarios(FILE *punteroFichero,tipoListaUsuarios listaUsuarios, tipoListaReproducciones listaReproducciones){
    char ruta [MAXNOMBRE];
    int fwControl;
    printf("\nIntroduzca la ruta del fichero");
    scanf("%s", ruta);
//Apertura del fichero escritura
    punteroFichero= fopen(ruta,"w");
    if (punteroFichero != NULL) {
        printf("El fichero de escritura se ha abierto correctamente.\n");
        printf(" Escribiendo...\n\n");
        //Escritura en el fichero
        for (int i = 0; i <= listaUsuarios.tope ; ++i) {
            fprintf(punteroFichero,"Usuario URJC: %s  Saldo: %.2f  Perfil: %s Reproducciones: %d\n",listaUsuarios.listaUsuarios[i].usuarioURJC, listaUsuarios.listaUsuarios[i].saldo,listaUsuarios.listaUsuarios[i].perfil,
                    contadorReproducciones(listaReproducciones, listaUsuarios.listaUsuarios[i].usuarioURJC));
        }

        relojArena();
//Cierre del fichero
        fwControl= fclose(punteroFichero);
        if (fwControl != 0) {
            printf("El fichero de escritura ha dado un error en el cierre.\n");
        } else {
            printf("El fichero de escritura se ha cerrado correctamente.\n");
        }
    } else {
        printf("El fichero de escritura ha dado un error de apertura.\n");
    }
}
void ordenarUsuariosAlfabeticamente(tipoListaUsuarios *lista){
    int i,j,contador;
    tipoUsuario aux;
    for(contador=0;contador<lista->tope;contador++){
        for(i=0,j=1;j<lista->tope;i++,j++){
            if(strcmp(lista->listaUsuarios[i].usuarioURJC,lista->listaUsuarios[j].usuarioURJC)>0){
                aux=lista->listaUsuarios[j];
                lista->listaUsuarios[j]=lista->listaUsuarios[i];
                lista->listaUsuarios[i]=aux;
            }
        }
    }
}
void ordenarId(tipoListaRecursos *lista) {
    int i, j, contador;
    tipoRecurso aux;
    for (contador = 0; contador < lista->tope; contador++) {
        for (i = 0, j = 1; j < lista->tope; i++, j++) {
            if (lista->listaRecursos[i].id > lista->listaRecursos[j].id) {
                aux = lista->listaRecursos[j];
                lista->listaRecursos[j] = lista->listaRecursos[i];
                lista->listaRecursos[i] = aux;
            }
        }
    }
}
void ordenarPorFecha(tipoListaReproducciones *lista) {
    int i, j, contador;
    tipoReproduccion aux;
    for (contador = 0; contador < lista->tope; contador++) {
        for (i = 0, j = 1; j < lista->tope; i++, j++) {
            if (strcmp(lista->listaReproduccion[i].fecha, lista->listaReproduccion[j].fecha) > 0) {
                aux = lista->listaReproduccion[j];
                lista->listaReproduccion[j] = lista->listaReproduccion[i];
                lista->listaReproduccion[i] = aux;
            }
        }
    }
}


/*
void bajaUsuario (tipoListaUsuarios *lista, tipoUsuario eliminado,tipoListaReproducciones *lista2) {
    int posicion, pos2;
    int i, j;
    posicion = buscarUsuarioURJC(*lista, eliminado.usuarioURJC);
    if (posicion == -1) {
        printf("El usuario no esta en la lista\n");
    } else {
        for (i = posicion; i < lista->tope; i++) {
            lista->listaUsuarios[i] = lista->listaUsuarios[i + 1];
        }
        lista->tope--;
        printf("Usuario eliminado\n");
    }
    do {
        pos2 = buscarReproduccionURJC(*lista2, eliminado.usuarioURJC);
        for (j = pos2; j < lista->tope; j++) {
            lista2->listaReproduccion[j] = lista2->listaReproduccion[j + 1];
        }
        lista2->tope--;
    } while (pos2!=-1);
    printf("Las reproducciones del usuario han sido eliminadas\n");
}
*/