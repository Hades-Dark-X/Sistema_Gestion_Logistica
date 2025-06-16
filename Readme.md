# Análisis Inicial y Detección de Limitaciones

<p>
Comenzamos con un análisis exhaustivo del código fuente para identificar las estructuras de datos existentes y comprender cómo el sistema gestiona la información de pedidos, vehículos y almacenes. Durante esta fase, se identificó una limitación significativa en la función actualizarAlmacen(), que originalmente utilizaba un std::vector para almacenar la información de los almacenes. Aunque funcional, esta elección presenta inconvenientes de eficiencia a medida que el volumen de datos aumenta.
</p>

### Tipos de Estructuras de Datos Utilizadas

A continuación, se describen las estructuras de datos relevantes encontradas en el sistema y sus implicaciones:

#### Estructuras de Datos No Lineales

- **`std::map<std::string, Pedido> pedidos_map;`**
  - Representa un **árbol de búsqueda**. Su estructura subyacente es un árbol balanceado.
  - Las **claves (IDs de los pedidos)** mantienen un orden, lo que permite búsquedas, inserciones y eliminaciones eficientes (O(logn)).
- **`std::unordered_map<std::string, std::list<Vehiculo>> vehiculos_graph;`**
  - Esta estructura se describe en el código como un **grafo**.
  - Un `std::unordered_map` es una **tabla hash**. Aquí, se utiliza para representar relaciones donde cada clave (ID del vehículo) se asocia con una lista de vehículos (`std::list<Vehiculo>`). Las operaciones promedio son de O(1).

#### Estructuras de Datos Lineales

- **`std::vector<Almacen> almacenes;`** (Versión original)
  - Los objetos `Almacen` se guardan uno tras otro, en un orden específico (similar a una lista o un arreglo).
  - Permite la búsqueda y actualización de información de un almacén específico, pero con una eficiencia de O(n) para búsquedas y O(n) para inserciones y eliminaciones en el peor de los casos.

---

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

### Optimización de la Gestión de Almacenes

La mejora implementada se centra en la función actualizarAlmacen(), donde se ha realizado una transición de un `std::vector` a un `std::map<std::string, Almacen>`. Esta elección estratégica de una estructura de datos no lineal (árbol de búsqueda) sienta las bases para futuras implementaciones de funciones como agregar, eliminar y gestionar almacenes, dotando al software de mayor funcionalidad, versatilidad y robustez.

### Código Comparativo:

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

### Código con la aplicación de la mejora

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

### Comparación de Eficiencia de Estructuras

| Estructura                        | Búsqueda | Insersión                                                                                                        | Problema             | Posible Mejora                                 |
| --------------------------------- | -------- | ---------------------------------------------------------------------------------------------------------------- | -------------------- | ---------------------------------------------- |
| `std::vector<Almacen> almacenes;` | O(n)     | O(n) ordena los elementos de manera secuencial; es decir, al final de la lista o arreglo                         | La búsqueda es lenta | `std::map<std::string, Almacen> almacenes_map` |
| `map<string, Pedido>`             | O(log n) | O(log n) Compara el dato con los que ya tiene y decide si va a la "izquierda" o a la "derecha" en su estructura. | N/A                  | Es óptimo                                      |
| `std::unordered_map`              | O(1) avg | O (1) avg ordena los datos mediante una clave y un valor                                                         | N/A                  | Es eficiente                                   |

**¿Por qué un Árbol es Más Eficiente?**

Un árbol, al ser una estructura de datos dinámica y no lineal, permite un recorrido y búsqueda de datos considerablemente más eficiente que una estructura lineal como un std::vector (lista o arreglo).

    Con un std::vector: Para encontrar un elemento específico, el sistema debe recorrer cada nodo uno por uno (O(n)), lo que resulta ineficiente si el elemento deseado se encuentra al final de la lista o si hay una gran cantidad de datos.

    Con un árbol binario (como std::map): Se realiza un descarte de datos de manera logarítmica (O(logn)). Por ejemplo, al buscar un almacén por su ID, el árbol compara el ID buscado con el nodo actual y decide si debe ir a la rama izquierda o derecha, descartando rápidamente la mitad de los datos restantes en cada paso. Esto se traduce en una búsqueda y actualización mucho más rápida, especialmente con grandes volúmenes de información.

El ordenamiento implícito en un std::map se da por la propia estructura del árbol binario, que mantiene los elementos ordenados por sus claves (en este caso, los IDs de pedidos o almacenes) de forma ascendente. Esto no requiere un algoritmo de ordenamiento explícito como Bubble Sort, Select Sort o Insertion Sort, ya que el orden se mantiene intrínsecamente durante las inserciones.
Propósito de actualizarAlmacen() y su Optimización

**Proposito de `actualizarAlmacen();` y su optimización**
La función actualizarAlmacen() tiene como propósito principal guardar y actualizar los datos de los almacenes. Anteriormente, esta función dependía de un std::vector para almacenar los datos. Como se explicó, esta implementación resultaba ineficiente a medida que aumentaba la cantidad de datos en los almacenes.

Para resolver este inconveniente y mejorar drásticamente el rendimiento, se implementó un árbol binario auto-balanceado (std::map) para el almacenamiento de los almacenes. Con esta mejora, el ordenamiento y la búsqueda de los almacenes se siguen llevando a cabo eficientemente por medio de sus IDs, pero con una complejidad logarítmica que garantiza un mejor desempeño.

---

### Análisis de funcionalidades `unordered_map`

La estructura `unordered_map<string, Vehiculo> vehiculos_graph` en sí no cuenta con un método de ordenamiento, aunque a primera vista ordenada por el `id` cuando buscamos o iteramos sobre el grafo, el orden no está garantizado.

`unordered_map` Lo que hace es, en el grafo, para almacenar los vehículos; usa el `id` para crear una lista que va a almacenar el vehículo dentro de ella.

| Estructura      | Orden | Uso Actual | Problema                                                                                       | Mejora propuesta       |
| --------------- | ----- | ---------- | ---------------------------------------------------------------------------------------------- | ---------------------- |
| `unordered_map` | N/A   | Vehículos  | No se garantiza ni se puede predecir el orden de los elementos con cada ejecución del programa | Implementar `std::map` |

### Propuesta de método de búsqueda

| Estructura | Orden    | Uso Actual | Solución                                                       | Mejora propuesta |
| ---------- | -------- | ---------- | -------------------------------------------------------------- | ---------------- |
| `std::map` | O(log n) | N/A        | No se garantiza ni se puede predecir el orden de los elementos | Ya es eficiente  |
