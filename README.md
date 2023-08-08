# Space bullet
##
## **Colaboradores**

---


<table>
  <tr>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/131840985?v=4" width="100px;" alt="Yasmin"/><br>
        <sub>
          <b>DEZA SOTOMAYOR FERNANDO DAVID</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/" width="100px;" alt="Joel"/><br>
        <sub>
          <b>MACHACA MUÑIZ JOSE ALEJANDRO</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/104391418?v=4" width="100px;" alt="Luis1"/><br>
        <sub>
          <b>PACHARI MILLIO GERALD</b>
        </sub>
      </a>
    </td>
     <td align="center">
      <a href="#">
        <img src="https://avatars.githubusercontent.com/u/133831781?v=4" width="100px;" alt="imanol"/><br>
        <sub>
          <b>ZEGARRA ROJAS MARIO DENIS</b>
        </sub>
      </a>
    </td>
     
     
     
  </tr>
</table>

## **Descripcion**
En Space Bullet, tendremos dos jugadores que se enfrentarán en un mapa espacial, por turnos
cronometrados de 20s, en los cuales trataran de obtener la victoria robando la estrella o derribando al
otro jugador (bajando su vida a 0%).
Cada jugador lanza proyectiles los cuales están afectados por la fuerza con la que fueron lanzados, por
la fuerza de gravedad, y la dirección de lanzamiento.
El juego "Space Bullet" presenta un emocionante sistema de runas o power ups que agrega una amplia
variedad de opciones y estrategias a las partidas. Estas poderosas runas ofrecen beneficios especiales a
los jugadores, brindando oportunidades tácticas para personalizar y mejorar sus habilidades de combate
en el vasto y peligroso espacio exterior.
Dentro de "Space Bullet", los jugadores encontrarán una selección de runas con funciones únicas:
1. Runa de Doble Daño: Esta runa hara que los ataques del jugador tengan el doble de daño.
2. Runa de Regeneración de Vida: Esta runa te concede la capacidad de regenerar vida de forma
   rápida y constante,
3. Runa de Inmunidad a Balas: Esta runa te otorga inmunidad frente a los ataques de proyectiles
   enemigos.
4. Runa de Velocidad de Movimiento: Permitirá que los personajes se puedan mover mas
   rápido.
   LISTADO DE CLASES:
1. Personaje (Diseño diseñoPersonaje, float vida, DireccionDisparo currentDireccion, Saltar(),
   Moverse(), Disparar())
2. Personaje1( Disparar()) //dispara 1 vez ,tiene mas daño,
3. Personaje2( Disparar()) //puede disparar 2 veces ,pero baja menos daño
4. Personaje3( Disparar()) //tiene más vida , y tiene mas rango de movimiento
5. DireccionDisparo (float dirX, float dirY)
6. Proyectil (float peso,float daño, Colisionar())
7. Runa( float multiplicadorVelocidad,float multiplicadorDaño,float multiplicadorVida, float
   multiplicadorResistenciaDaño, AplicarHabilidades())
8. RunaDobleDanio(AplicarHabilidades())
9. RunaRegeneracionVida(AplicarHabilidades())
10. RunaInmunidad(AplicarHabilidades())
11. RunaVelocidad(AplicarHabilidades())
12. Mapa (string nombre, float gravedad, DisenioMapa geometriaMapa , Runa[] listaRunas)
13. DisenioMapa ( int ancho, int altura)
14. Disenio( int ancho, int altur


![Imagen_Juego](../test/Capture01.png)
