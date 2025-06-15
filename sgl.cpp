#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cstdlib> // Necesario para la función salir

using namespace std;

// Estructura para representar un pedido
struct Pedido {
    string id;
    string descripcion;
    string idVehiculo; // Agregamos un campo para el id del vehiculo asignado
};

// Estructura para representar un vehiculo
struct Vehiculo {
    string id;
    string descripcion;
    bool disponible;
};

// Estructura para representar un almacen
struct Almacen {
    string id; // ID del almacen
    string descripcion; // Descripcion del almacen
    int cantidad; // Cantidad de productos en el almacen
};

// Árbol para almacenar los pedidos (map ordenado por ID)
std::map<std::string, Pedido> pedidos_map;

// Grafo para almacenar los vehiculos (mapa no ordenado con listas de adyacencia)
std::unordered_map<std::string, std::list<Vehiculo>> vehiculos_graph;

// Basado en el árbol de pedidos usare la misma estructura no lineal para los almacenes
std::map<std::string, Almacen> almacenes_map;

void agregarPedido() {
    Pedido nuevoPedido;
    cout << "Ingrese el ID del pedido: ";
    cin >> nuevoPedido.id;
    cin.ignore(); // Para limpiar el buffer de entrada

    // Verificamos si ya existe un pedido con el mismo ID
    if (pedidos_map.find(nuevoPedido.id) != pedidos_map.end()) {
        cout << "Ya existe un pedido con ese ID. Ingrese otro ID." << endl;
        return;
    }

    cout << "Ingrese la descripcion del pedido: ";
    getline(cin, nuevoPedido.descripcion);

    // Inicialmente, no hay ningún vehículo asignado al pedido
    nuevoPedido.idVehiculo = "";

    // Agregamos el pedido al árbol de pedidos
    pedidos_map[nuevoPedido.id] = nuevoPedido;

    cout << "Pedido agregado exitosamente." << endl;
}

// Función para eliminar un pedido
void eliminarPedido() {
    string idPedido;
    cout << "Ingrese el ID del pedido a eliminar: ";
    cin >> idPedido;

    // Eliminamos el pedido del árbol
    if (pedidos_map.erase(idPedido) > 0) {
        cout << "Pedido eliminado exitosamente." << endl;
    } else {
        cout << "No se encontró el pedido con el ID ingresado." << endl;
    }
}

// Función para modificar un pedido
void modificarPedido() {
    string idPedido;
    cout << "Ingrese el ID del pedido a modificar: ";
    cin >> idPedido;

    // Buscamos el pedido en el árbol
    auto itPedido = pedidos_map.find(idPedido);

    if (itPedido != pedidos_map.end()) {
        cout << "Ingrese la nueva descripcion del pedido: ";
        cin.ignore();
        getline(cin, itPedido->second.descripcion);
        cout << "Pedido modificado exitosamente." << endl;
    } else {
        cout << "No se encontró el pedido con el ID ingresado." << endl;
    }
}

// Implementacion de la funcion buscarPedido
void buscarPedido() {
    // Solicitamos el ID del pedido
    std::string idPedido;
    std::cout << "Ingrese el ID del pedido que desea buscar: ";
    std::cin >> idPedido;

    // Realizamos la busqueda en el mapa
    auto it = pedidos_map.find(idPedido);

    if (it != pedidos_map.end()) {
        std::cout << "Descripcion del pedido: " << it->second.descripcion << std::endl;
    } else {
        std::cout << "El pedido no existe" << std::endl;
    }
}

// Funcion para gestionar un pedido
void gestionarPedido() {
    int opcion;

    do {
        cout << "\nGestion de Pedidos\n";
        cout << "1. Agregar pedido\n";
        cout << "2. Buscar pedido\n";
        cout << "3. Eliminar pedido\n";
        cout << "4. Modificar pedido\n";
        cout << "5. Volver al menu principal\n";
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarPedido();
                break;
            case 2:
                buscarPedido();
                break;
            case 3:
                eliminarPedido();
                break;
            case 4:
                modificarPedido();
            case 5:
                break;
            default:
                cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                break;
        }
    } while (opcion != 5);
}

// Funcion para eliminar un vehiculo
void eliminarVehiculo() {
    string id;
    cout << "Ingrese el ID del vehiculo a eliminar: ";
    cin >> id;

    // Eliminamos el vehiculo del grafo
    if (vehiculos_graph.erase(id) > 0) {
        cout << "Vehiculo eliminado exitosamente." << endl;
    } else {
        cout << "No se encontró el vehiculo con el ID proporcionado." << endl;
    }
}

// Función para agregar un vehiculo
void agregarVehiculo() {
    Vehiculo nuevoVehiculo;

    cout << "Ingrese el ID del vehiculo: ";
    cin >> nuevoVehiculo.id;
    cin.ignore(); // Para limpiar el buffer de entrada

    cout << "Ingrese la descripcion del vehiculo: ";
    getline(cin, nuevoVehiculo.descripcion);

    nuevoVehiculo.disponible = true;

    // Agregamos el vehiculo al grafo
    vehiculos_graph[nuevoVehiculo.id].push_back(nuevoVehiculo); 

    cout << "Vehiculo agregado exitosamente." << endl;
}

// Funcion para modificar un vehiculo
void modificarVehiculo() {
    string id;
    cout << "Ingrese el ID del vehiculo a modificar: ";
    cin >> id;

    auto it = vehiculos_graph.find(id);
    if (it != vehiculos_graph.end()) {
        for (auto& vehiculo : it->second) { // Iteramos sobre la lista de vehículos con el mismo ID
            if (vehiculo.id == id) {
                cout << "Ingrese la nueva descripcion del vehiculo: ";
                cin.ignore();
                getline(cin, vehiculo.descripcion);

                cout << "Vehiculo modificado exitosamente." << endl;
                return;
            }
        }
    }

    cout << "No se encontró el vehiculo con el ID proporcionado." << endl;
}

// Función para buscar un vehiculo
void buscarVehiculo() {
    // Solicitamos el ID del vehículo
    std::string idVehiculo;
    std::cout << "Ingrese el ID del vehiculo que desea buscar: ";
    std::cin >> idVehiculo;

    // Realizamos la busqueda en el grafo de vehiculos
    auto it = vehiculos_graph.find(idVehiculo);

    if (it != vehiculos_graph.end()) {
        // En un grafo, la clave es el ID, y el valor es una lista de vehículos.
        if (!it->second.empty()) {
            const Vehiculo& vehiculoEncontrado = it->second.front(); // Tomamos el primer vehículo en la lista
            std::cout << "Descripcion del vehiculo: " << vehiculoEncontrado.descripcion << std::endl;
            std::cout << "Disponibilidad: " << (vehiculoEncontrado.disponible ? "Disponible" : "No disponible") << std::endl;
        } else {
            std::cout << "El vehiculo con el ID ingresado no tiene informacion detallada." << std::endl;
        }
    } else {
        std::cout << "El vehiculo no existe" << std::endl;
    }
}

// Funcion para gestionar un vehiculo
void gestionarVehiculo() {
    int opcion;

    do {
        cout << "\nGestion de Vehiculos\n"; // Cambiado para claridad
        cout << "1. Agregar vehiculo\n";
        cout << "2. Buscar vehiculo\n"; // Nueva opción
        cout << "3. Eliminar vehiculo\n";
        cout << "4. Modificar vehiculo\n";
        cout << "5. Regresar al menu principal\n"; // Opción ajustada
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarVehiculo();
                break;
            case 2:
                buscarVehiculo();
                break;
            case 3:
                eliminarVehiculo();
                break;
            case 4:
                modificarVehiculo();
                break;
            case 5:
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 5);
}


// Funcion para asignar un vehiculo a un pedido
void asignarVehiculo() {
    string idPedido, idVehiculo;
    cout << "Ingrese el ID del pedido: ";
    cin >> idPedido;
    cout << "Ingrese el ID del vehiculo: ";
    cin >> idVehiculo;

    // Buscamos el pedido en el árbol de pedidos
    auto itPedido = pedidos_map.find(idPedido);
    // Buscamos el vehiculo en el grafo
    auto itVehiculo = vehiculos_graph.find(idVehiculo);

    if (itPedido != pedidos_map.end() && itVehiculo != vehiculos_graph.end()) {
        for (auto& vehiculo : itVehiculo->second) { // Iteramos sobre la lista de vehículos con el mismo ID
            if (vehiculo.disponible) {
                itPedido->second.idVehiculo = idVehiculo;
                vehiculo.disponible = false;
                cout << "Vehiculo asignado exitosamente al pedido." << endl;
                return;
            }
        }
        cout << "No hay vehículos disponibles con ese ID." << endl;
    } else {
        cout << "No se pudo asignar el vehiculo al pedido. Verifique los IDs ingresados." << endl;
    }
}

// Funcion para consultar el estado de un envio
void consultarEstado() {
    string idPedido;
    cout << "Ingrese el ID del pedido: ";
    cin >> idPedido;

    // Buscamos el pedido en el árbol de pedidos
    auto itPedido = pedidos_map.find(idPedido);

    if (itPedido != pedidos_map.end()) {
        cout << "ID del pedido: " << itPedido->first << endl;
        cout << "Descripcion del pedido: " << itPedido->second.descripcion << endl;
        cout << "ID del vehiculo asignado: " << (itPedido->second.idVehiculo.empty() ? "Ninguno" : itPedido->second.idVehiculo) << endl;
    } else {
        cout << "No se encontró el pedido con el ID ingresado." << endl;
    }
}

// Funcion para planificar una ruta de transporte
void planificarRuta() {
    string idPedido;
    cout << "Ingrese el ID del pedido para el que se planificara la ruta: ";
    cin >> idPedido;

    // Buscamos el pedido en el árbol de pedidos
    auto itPedido = pedidos_map.find(idPedido);

    // Verificamos que el pedido exista y que tenga un vehículo asignado
    if (itPedido != pedidos_map.end() && !itPedido->second.idVehiculo.empty()) {
        // Aquí iría la lógica para planificar la ruta, 
        // utilizando itPedido->second para acceder a los datos del pedido

        // Ejemplo (lógica simplificada):
        string idVehiculoAsignado = itPedido->second.idVehiculo;
        cout << "Ruta planificada para el pedido " << idPedido 
             << " con el vehiculo " << idVehiculoAsignado << endl;

        // ... (Lógica real de planificación de ruta)

    } else {
        cout << "No se pudo planificar la ruta. Verifique que el ID del pedido es correcto y que tiene un vehiculo asignado." << endl;
    }
}

// Funcion para verificar la disponibilidad de vehiculos
void verificarDisponibilidad() {
    for (const auto& pair : vehiculos_graph) {
        for (const auto& vehiculo : pair.second) {
            if (vehiculo.disponible) {
                cout << "ID del vehiculo: " << vehiculo.id << endl;
                cout << "Descripcion del vehiculo: " << vehiculo.descripcion << endl;
            }
        }
    }
}

// Funcion para agregar almacen
void agregarAlmacen() {
    Almacen nuevoAlmacen;
    cout << "Ingrese el ID del almacen: ";
    cin >> nuevoAlmacen.id;
    cin.ignore(); // Para limpiar el buffer

    if (almacenes_map.count(nuevoAlmacen.id)) {
        cout << "Ya existe un almacen con ese ID." << endl;
        return;
    }else{
        cout << "Ingrese la descripcion del almacen: ";
        getline(cin, nuevoAlmacen.descripcion);
        cout << "Ingrese la cantidad inicial de productos: ";
        cin >> nuevoAlmacen.cantidad;

        almacenes_map[nuevoAlmacen.id] = nuevoAlmacen;
        cout << "Almacen agregado exitosamente." << endl;
    }
}

// Función para listar todos los almacenes (ya estarán ordenados por ID)
void listarAlmacenes() {
    if (almacenes_map.empty()) {
        cout << "No hay almacenes registrados." << endl;
        return;
    }
    for (const auto& pair : almacenes_map) {
        cout << "ID: " << pair.first
             << ", Descripcion: " << pair.second.descripcion
             << ", Cantidad: " << pair.second.cantidad << endl;
    }
}


// Funcion para actualizar la informacion de un almacen
void actualizarAlmacen() {
    string idAlmacen;

    cout << "Ingrese el ID del almacen: ";
    cin >> idAlmacen;
     cin.ignore();

    // Buscamos el almacen en el mapa de almacenes
    auto itAlmacen = almacenes_map.find(idAlmacen);

    // Verificamos que el almacen exista
    if (itAlmacen != almacenes_map.end()) {

        string nuevaDescripcion;
        cout << "Ingrese la nueva descripcion del almacen (deje vacio para no cambiar): ";
        getline(cin, nuevaDescripcion);

        // Solo actualiza si el usuario ingresó algo
        if (!nuevaDescripcion.empty()) { 
            itAlmacen->second.descripcion = nuevaDescripcion;
            cout << "Descripcion del almacen actualizada exitosamente." << endl;
        }

        int nuevaCantidad;
        cout << "Ingrese la nueva cantidad de productos en el almacen (o -1 para no cambiar): ";
        cin >> nuevaCantidad;

        if (nuevaCantidad != -1) {
            itAlmacen->second.cantidad = nuevaCantidad;
            cout << "Cantidad de productos del almacen actualizada exitosamente." << endl;
        }
          cout << "Informacion del almacen actualizada exitosamente." << endl; 
    } else {
        cout << "No se encontro el almacen con el ID ingresado." << endl;
    }
}


// Funcion para eliminar almacen
void eliminarAlmacen() {
    string idAlmacen;
    cout << "Ingrese el ID del almacen a eliminar: ";
    cin >> idAlmacen;

    if (almacenes_map.erase(idAlmacen) > 0) {
        cout << "Almacen eliminado exitosamente." << endl;
    } else {
        cout << "No se encontro el almacen con el ID ingresado." << endl;
    }
}

void gestionarAlmacenes() {
    int opcion;
    do {
        cout << "\nGestion de Almacenes\n";
        cout << "1. Agregar Almacen\n";
        cout << "2. Listar Almacenes \n";
        cout << "3. Actualizar Informacion de Almacen\n";
        cout << "4. Eliminar Almacen\n";
        cout << "5. Volver al menu principal\n"; // La opción para salir es 5
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarAlmacen();
                break;
            case 2:
                listarAlmacenes();
                break;
            case 3:
                actualizarAlmacen();
                break;
            case 4:
                eliminarAlmacen();
                break;
            case 5:
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);
}

// Funcion para salir del sistema
void salir() {
    std::cout << "Saliendo del programa..." << std::endl;
    // Llama a exit() con un código de estado. 0 indica una salida exitosa.
    exit(0);
}

int main() {
    int opcion;

    do {
        cout << "\nSistema de Gestion Logistica\n";
        cout << "1. Gestionar pedido\n";
        cout << "2. Gestionar vehiculo\n";
        cout << "3. Asignar vehiculo a pedido\n";
        cout << "4. Consultar estado de envio\n";
        cout << "5. Planificar ruta de transporte\n";
        cout << "6. Verificar disponibilidad de vehiculos\n";
        cout << "7. Gestionar almacen\n";
        cout << "8. Salir\n";
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                gestionarPedido();
                break;
            case 2:
                gestionarVehiculo();
                break;
            case 3:
                asignarVehiculo();
                break;
            case 4:
                consultarEstado();
                break;
            case 5:
                planificarRuta();
                break;
            case 6:
                verificarDisponibilidad();
                break;
            case 7:
                gestionarAlmacenes();
                break;
            case 8:
                salir();
                break;
            default:
                cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                break;
        }
    } while (opcion != 8);

    return 0;
}