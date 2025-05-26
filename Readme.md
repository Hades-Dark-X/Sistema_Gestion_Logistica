<p>
 Se detalla el proceso de análisis, mejora e implementación realizado sobre el Sistema de Gestión Logística (SGL), específicamente en su versión SGL_U2.cpp. El objetivo principal de este proyecto es optimizar la eficiencia del SGL, enfocándose inicialmente en la gestión de almacenes, un componente crítico para las operaciones logísticas.
 </p>

<p>
Inicialmente, se realizó un análisis preliminar del código fuente para identificar las estructuras de datos existentes y comprender cómo el sistema manejaba la información de pedidos, vehículos y almacenes. Se detectó que la función de actualización de almacenes, actualizarAlmacen(), dependía de un std::vector para almacenar la información, una elección que, si bien funcional, presenta limitaciones significativas
</p>

<p>
De igual manera se pretende que el estudiante se adrente a lo que son las estructuras lineales y no lineales, para que sea capaz de manejar tipos de datos abstractos más complejos.
</p>

---

### Tipos de estructuras

| Estructura de datos no lineales                                         |                                                                                                                                                                                                                                                           |
| ----------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `std::map<std::string, Pedido> pedidos_map;`                            | Representa un **árbol de búsqueda** su estructura subyacente es un árbol. Las claves (IDs de los pedidos) mantienen un orden, lo que permite búsquedas, inserciones y eliminaciones eficientes                                                            |
| `std::unordered_map<std::string, std::list<Vehiculo>> vehiculos_graph;` | Esta estructura se describe en el código como un **grafo**. Un `std::unordered_map` es una **tabla hash**. Aquí, se utiliza para representar la relación donde cada clave (ID del vehículo) se relaciona con una lista de vehículos `std::list<Vehiculo>` |
| Estructura de datos lineal                                              |                                                                                                                                                                                                                                                           |
| `std::vector<Almacen> almacenes;`                                       | Esto significa que los objetos `Almacen` se guardan uno tras otro, en un orden específico (similar a una lista o un arreglo). Permitir la búsqueda y actualización de información de un almacén específico.                                               |

### Análisis de funcionalidades del árbol `Pedido`

| Nombre de la función | Descripción                                                                                                                                                                                                                            |
| -------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `agregarPedido`      | Esta función solícita al usuario un `id`, si existe un pedido con ese `id ` envía un mensaje notificando que existe ese id a un pedido asignado, de lo contrario se solícita una descripción de pedido y se asigna al árbol de pedidos |
| `eliminarPedido`     | Esta función se encarga de eliminar elementos dentro del árbol de pedidos por medio de un `id`, si el id existe procede a eliminar el elemento con ese id; de lo contrario se notifica que el id no existe                             |
| `modificarPedido`    | Por medio de esta función podemos actualizar los datos de un pedido existente por medio de su id, ingresando una nueva descripción que sobrescribe los datos anteriores de la descripción                                              |
| `gestionarPedido`    | Esta función actúa como un menú que permite administrar las otras funciones del CRUD de pedido mediante un bucle `do while` un `switch`                                                                                                |

### Análisis de las funcionalidades del Grafo Vehículo

| Nombre de la función | Descripción                                                                                                                                                                                                               |
| -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `agregarVehiculo`    | Esta función solícita al usuario un `id`, para un nuevo `vehiculo ` y una `descripcion`, quiero suponer que se utiliza un grafo para relacionar un modelo de vehículo a varias unidades del mismo auto                    |
| `eliminarVehiculo`   | Esta función se encarga de eliminar elementos dentro de la estructura de `vehiculo` por medio de un `id`, si el id existe procede a eliminar el elemento con ese id; de lo contrario se notifica que el id no se encontró |
| `modificarVehiculo`  | Por medio de esta función podemos actualizar los datos de un vehículo existente por medio de su id, ingresando una nueva descripción que sobrescribe los datos anteriores de la descripción                               |
| `gestionarVehiculo`  | Esta función actúa como un menú que permite administrar las otras funciones del CRUD de pedido mediante un bucle `do while` un `switch`                                                                                   |
| `asignarVehiculo`    | Se encarga de asignar un vehículo a un pedido si el vehículo está disponible, de lo contrario notifica que el auto no está disponible.                                                                                    |

### Análisis del vector Almacén

| Estructura de datos lineal        |                                                                                                                                                                                                             |
| --------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `std::vector<Almacen> almacenes;` | Esto significa que los objetos `Almacen` se guardan uno tras otro, en un orden específico (similar a una lista o un arreglo). Permitir la búsqueda y actualización de información de un almacén específico. |
| Estructura no lineal              |                                                                                                                                                                                                             |
| `std::map<std::string`            | Ahora `map::find` realiza una búsqueda logarítmica (mucho más rápida para grandes cantidades de datos) para encontrar el almacén por su ID.                                                                 |

### Función original `actualizarAlmacen`

```C++
void actualizarAlmacen() {
string idAlmacen;
int nuevaCantidad;

cout << "Ingrese el ID del almacen: ";
cin >> idAlmacen;

// Buscamos el almacen en el vector de almacenes
auto itAlmacen = find_if(almacenes.begin(), almacenes.end(), [&idAlmacen](const Almacen& almacen) { return almacen.id == idAlmacen; });

// Verificamos que el almacen exista
if (itAlmacen != almacenes.end()) {

     // Solicitamos la nueva cantidad de productos en el almacen
     cout << "Ingrese la nueva cantidad de productos en el almacen: ";
     cin >> nuevaCantidad;

     // Actualizamos la cantidad de productos en el almacen
     itAlmacen->cantidad = nuevaCantidad;
     cout << "Informacion del almacen actualizada exitosamente." << endl;
} else {
     cout << "No se encontro el almacen con el ID ingresado." << endl;
	}
}
```

### Código con un árbol para hacer el código más eficiente en la búsqueda y actualización de almacenes

```C++
void actualizarAlmacen() {
string idAlmacen;
int nuevaCantidad;

cout << "Ingrese el ID del almacen: ";
cin >> idAlmacen;

// Buscamos el almacen en el mapa de almacenes
auto itAlmacen = almacenes_map.find(idAlmacen);

// Verificamos que el almacen exista
if (itAlmacen != almacenes_map.end()) {
    
     // Solicitamos la nueva cantidad de productos en el almacen
     cout << "Ingrese la nueva cantidad de productos en el almacen: ";
     cin >> nuevaCantidad;

     // Actualizamos la cantidad de productos en el almacen
     itAlmacen->second.cantidad = nuevaCantidad;
     cout << "Informacion del almacen actualizada exitosamente." << endl;
} else {
     cout << "No se encontro el almacen con el ID ingresado." << endl;
	}
}
```

<p>
La mejora actual se centra en mejorar la búsqueda para la función actualizarAlmacen, la elección de un **árbol** **sentará las bases para futuras implementaciones** de agregar, eliminar y gestionar. Que es lo que dotará de mayor funcionalidad, versatilidad y robustez al software en su conjunto
</p>

### ¿Cómo es que un árbol es más eficiente?

<p>
Un árbol es una estructura dinámica no lineal por lo que podemos recorrer el árbol de manera recursiva lo que hace el recorrido más eficiente en lugar de una lista que es una estructura lineal.
</p>

<p>
Con un vector como una lista tenemos que recorrer forzosamente nodo por nodo hasta hallar el que nos interesa, si el almacén que necesitamos se encuentra cerca del final de la lista esto implica recorrer todos los almacenes anteriores lo que es más tardado.
</p>

<p>
Con un árbol binario lo que podemos es ir realizando un descarte de datos en este caso se hace un descarte por medio del id del almacén comparando si es mayor o menor que el nodo actual para realizar un descarte más rápido y por ende eficiente.
</p>

<p>
Si se implementa en próximas versiones las funciones de agregarAlmacen, eliminarAlmacen y gestionarAlmacen estas funciones se van a ver beneficiadas de la eficacia del árbol.
</p>

### Reflexión.

<p>
Este trabajo representó un reto primero para identificar que estructuras estaban implementadas en el código, para después entender; cómo trabajaban estructuras lineales, como pueden ser pilas, colas y listas.
</p>

<p>
Otro desafío fue enfrentar el hecho de que la funcionalidad de actualizarAlmacen parecía no tener relación con alguna parte funcional del código esto hasta que te das cuenta de queque el software se encuentra incompleto en su funcionalidad y falta dotarlo de más características.
</p>
