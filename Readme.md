# Análisis Inicial y Detección de Limitaciones

<p>
Comence con un análisis del código fuente para identificar las estructuras de datos existentes y comprender cómo el sistema maneja la información de pedidos, vehículos y almacenes. Durante esta fase, me percate de una limitación significativa en la función actualizarAlmacen(), que dependía de un std::vector para almacenar la información de los almacenes. Si bien  es funcional, esta elección presenta inconvenientes de eficiencia a medida que el volumen de datos aumenta.
</p>

<p>
Como parte de este proyecto, se busca que el estudiante se familiarice con las estructuras de datos lineales y no lineales, lo que le permitirá manejar tipos de datos abstractos más complejos y mejorar el rendimiento del software.
</p>

<p>
A continuación, se presenta una descripción de las estructuras de datos relevantes utilizadas y sus implicaciones:
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

### Optimización de la Gestión de Almacenes

<p>
La mejora actual se centra en la función actualizarAlmacen, donde hemos pasado de utilizar un std::vector a un std::map<std::string, Almacen>. Esta elección estratégica de una estructura de datos no lineal (árbol de búsqueda) sentará las bases para futuras implementaciones de las funciones de agregar, eliminar y gestionar almacenes, dotando al software de mayor funcionalidad, versatilidad y robustez.
</p>

<p>Código Comparativo:</p>

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

| Estructura                        | Búsqueda | Insersión                                                                                                        | Problema             | Posible Mejora                                 |
| --------------------------------- | -------- | ---------------------------------------------------------------------------------------------------------------- | -------------------- | ---------------------------------------------- |
| `std::vector<Almacen> almacenes;` | O(n)     | O(n) ordena los elementos de manera secuencial; es decir, al final de la lista o arreglo                         | La búsqueda es lenta | `std::map<std::string, Almacen> almacenes_map` |
| `map<string, Pedido>`             | O(log n) | O(log n) Compara el dato con los que ya tiene y decide si va a la "izquierda" o a la "derecha" en su estructura. | N/A                  | Es óptimo                                      |
| `std::unordered_map`              | O(1) avg | O (1) avg ordena los datos mediante una clave y un valor                                                         | N/A                  | Es eficiente                                   |

<p>
¿Por qué un árbol es más eficiente?

Un árbol, al ser una estructura de datos dinámica y no lineal, permite un recorrido y búsqueda de datos considerablemente más eficiente que una estructura lineal como un std::vector (lista o arreglo).

- Con un std::vector: Para encontrar un elemento específico, el sistema debe recorrer cada nodo uno por uno (O(n)), lo que resulta ineficiente si el elemento deseado se encuentra al final de la lista o si hay una gran cantidad de datos.

- Con un árbol binario (como std::map): Se realiza un descarte de datos de manera logarítmica (O(log n)). Por ejemplo, al buscar un almacén por su ID, el árbol compara el ID buscado con el nodo actual y decide si debe ir a la rama izquierda o derecha, descartando rápidamente la mitad de los datos restantes en cada paso. Esto se traduce en una búsqueda y actualización mucho más rápida, especialmente con grandes volúmenes de información.
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

### Análisis de funcionalidades

- Identifica el método de ordenamiento utilizado implícitamente en la estructura de datos no lineal `std::map<std::string, Pedido> pedidos_map;`

- Aquí debo mencionar que la estructura no cuenta con un algoritmo de ordenamiento como pueden ser; Bubble Sort, Select Sort o Insertion Sort por mencionar algunos.

- El ordenamiento implícito se lo otorga la estructura no lineal con la que se están almacenando los datos que en este caso es un Árbol binario, el ordenamiento se realiza de manera ascendente por medio del ID del pedido.

### Examina la función actualizarAlmacen() y comprende su propósito

- Anteriormente la estuctura que almacenaba los datos de actualizarAlmacen era un vector como se explico con anterioridad, su propósito es guardar los datos de los almacenes.

- Como ya se ha comentado al llevar a cabo su función por medio de un vector esto se vuelve ineficiente a medida que tenemos más y más datos en los almecenes.

- Para resolver este inconveniente se implemento un árbol binario auto- balanceado, dondé el ordenameinto se sigue llevando por medio del id de los almacenes.
