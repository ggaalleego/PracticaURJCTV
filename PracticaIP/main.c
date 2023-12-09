#include <stdio.h>
#include <string.h>
#define MAXNOMBRE 20
#define MAXAPELLIDO 50
#define MAXDNI 9
#define MAXCHARUSUARIO 9
#define MAXPERFIL 5
#define MAXTITULO 50
#define MAXAMBITO 20
#define MAXGENERO 20
#define MAXFECHA 10
#define MAXUSUARIOS 50 //nÃºmero mÃ¡ximo de usuarios
#define MAXRECURSOS 70 //nÃºmero mÃ¡ximo de recursos
#define MAXREPRODUCCIONES 80 //nÃºmero mÃ¡ximo de reproducciones

//usuario
typedef struct {
    char nombre[MAXNOMBRE];
    char apellidos[MAXAPELLIDO];
    char dni[MAXDNI];
    char usuarioURJC[MAXCHARUSUARIO];
    float saldo;
    char perfil[MAXPERFIL];
} tipoUsuario;

// recursos
typedef struct {
    int id;
    char titulo[MAXTITULO];
    char ambito[MAXAMBITO];
    char genero [MAXGENERO];
    float coste;
    int duracion;
} tipoRecurso;
// reproducciones
typedef struct {
    char fecha[MAXFECHA];
    char usuarioURJC[MAXCHARUSUARIO];
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
void leerUsuario (tipoUsuario *nuevoUsuario);
void mostrarUsuario (tipoUsuario usuario);
int buscarUsuarioURJC (tipoListaUsuarios lista, char UsuarioURJC[MAXCHARUSUARIO]);
void altaUsuario (tipoListaUsuarios *lista, tipoUsuario nuevo);
void bajaUsuario (tipoListaUsuarios *lista, tipoUsuario eliminado);
void cargarUsuarios(FILE *punteroFichero,tipoListaUsuarios listaDeUsuarios);
void cargarRecursos(FILE *punteroFichero,tipoListaRecursos listaDeRecursos );
void cargarReproducciones(FILE *punteroFichero,tipoListaReproducciones listaDeReproducciones);
int main() {
    char opcion;
    tipoUsuario usuario;
    FILE *pFichero;
    tipoListaUsuarios listaUsuarios;

    do{
        fflush(stdin);
        menu();
        scanf("%c",&opcion);
        switch (opcion){
            case 'A':
	     	 case 'a':
                printf("Alta usuario\n");
                break;
            case 'B':
                case 'b':
                printf("Baja usuario\n");
                break;
		case 'C':
            case 'c':
                printf("Alta recurso multimedia\n");
                break;
            case 'd':
		case 'D':
                printf("Baja recurso multimedia\n");
                break;
            case 'E':
		 case 'e':
                printf("Listado usuarios\n");
                break;
            case 'F':
		case 'f':
                printf("Listado recursps multimedia\n");
                break;
        case 'G':
            case 'g':
                printf("Listado reproducciones\n");
                break;
            case 'H':
            case 'h':
                printf("Reproduccion de un recurso multimedia por un usuario\n");
                break;
		 case 'I':
            case 'i':
                printf("Guardar usuarios\n");
                break;
		 case 'J':
            case 'j':
                printf("Guardar recursos multimedia\n");
                break;
		 case 'K':
            case 'k':
                printf("Guardar reproducciones\n");
                break;
		case 'L':
            case 'l':
                printf("Cargar usuarios\n");
                break;
		case 'M':
            case 'm':
                printf("Cargar recursos multimedia\n");
                break;
		case 'N':
            case 'n':
                printf("Cargar reproducciones\n");
                break;
		case 'O':
            case 'o':
                printf("Generar informe de usuarios en archivo\n");
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
void leerUsuario (tipoUsuario *nuevoUsuario){
    printf("Nombre del usuario: ");
    scanf("%s\n", nuevoUsuario->nombre);
    printf("Apellidos del usuario: ");
    scanf("%s\n", nuevoUsuario->apellidos);
    printf("DNI del usuario: ");
    scanf("%s\n", nuevoUsuario->dni);
    printf("Usuario URJC: ");
    scanf("%s\n", nuevoUsuario->usuarioURJC);
    nuevoUsuario->saldo=1000;
    printf("Perfil del usuario: ");
    scanf("%s\n", nuevoUsuario->perfil);
}

void mostrarUsuario (tipoUsuario usuario){
    printf("\n Nombre: %s", usuario.nombre);
    printf("\n Apellidos: %s", usuario.apellidos);
    printf("\n DNI: %s", usuario.dni);
    printf("\n Usuario URJC: %s", usuario.usuarioURJC);
    printf("\n Saldo: %f", usuario.saldo);
    printf("\n Perfil: %s", usuario.perfil);
}

int buscarUsuarioURJC (tipoListaUsuarios lista, char usuarioURJC[MAXCHARUSUARIO]) {
    int i;
    i = 0;
    while ((i < lista.tope) && (strcmp(usuarioURJC, lista.listaUsuarios[i].usuarioURJC) != 0)) {
        i++;
    }
    if (i > lista.tope) {
        i = -1;
    }
    return i;
}

void altaUsuario (tipoListaUsuarios *lista, tipoUsuario nuevo){
    int posicion;
    if(lista->tope>=MAXUSUARIOS){
        printf("La lista de usuarios esta llena, no se puede aÃ±adir el usuario\n");
    }
    else{
        posicion= buscarUsuarioURJC(*lista, nuevo.usuarioURJC);
        if(posicion == -1){
            lista->listaUsuarios[lista->tope]=nuevo;
            lista->tope++;
            printf("Usuario aÃ±adido\n");
        }
        else{
            printf("Usuario URJC repetido, no se puede aÃ±adir\n");
        }
    }
}

void bajaUsuario (tipoListaUsuarios *lista, tipoUsuario eliminado){
    int posicion;
    int i;
    posicion = buscarUsuarioURJC(*lista, eliminado.usuarioURJC);
    if (posicion==-1){
        printf("El usuario no esta en la lista\n");
    }
    else{
        for (i=posicion;i<lista->tope;i++){
            lista->listaUsuarios[i]=lista->listaUsuarios[i+1];
        }
        lista->tope--;
        printf("Usuario eliminado\n");
    }
}

void cargarUsuarios(FILE *punteroFichero,tipoListaUsuarios listaDeUsuarios){
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
              // altaUsuario( listaDeUsuarios, usuario);
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
void cargarRecursos(FILE *punteroFichero,tipoListaRecursos listaDeRecursos ){
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
                //altaRecurso( listaDeRecursos, recurso);
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
void cargarReproducciones(FILE *punteroFichero,tipoListaReproducciones listaDeReproducciones){
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
