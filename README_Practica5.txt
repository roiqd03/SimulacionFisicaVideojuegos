Práctica 5
Asignatura: Simulación física para videojuegos
Nombre: Roi Quintas Diz


Para esta práctica, he creado una nueva clase (Entity), de la que heredan tanto Particle
como RigidSolid (la cual también es nueva). De esta forma, en los sistemas, los generadores 
y los generadores de fuerzas, se interpreta cualquier partícula o sólido rígido como si fuese 
una entidad. Por ello, aunque las clases mantienen sus nombres (ParticleSystem, ParticleGenerator...),
se pueden utilizar ambos tipos de entidades simultaneamente.

Para probarlo, en el initPhysics() del archivo main.cpp se encuentra la constructora del ParticleSystem.
Por defecto, está puesto el RigidSolidSystem, que combina tanto partículas como sólidos rígidos. 
Se puede cambiar el sistema comentando esa linea y descomentando alguna de las de arriba. 
El PruebasSystem contiene la entrega de la práctica 3, con los generadores de fuerzas. Cabe destacar que el RigidSolidSystem
contiene los mismos generadores de partículas y de fuerzas, lo único que cambian son las partículas/sólidos
rígidos que se usan como modelos, por lo que se pueden comparar ambos sistemas. Además, con la tecla
'U' se puede usar la explosión en RigidSolidSystem, y con la tecla 'I' en PruebasSystem.

He quitado la gravedad que utiliza physx en la escena, ya que mis generadores de fuerzas están 
asociados a los generadores de entidades. Entonces, si quiero generar sólidos rígidos y 
partículas con el mismo generador, para que se le aplique el generador de fuerza de gravedad
a las partículas, también le tiene que afectar a los sólidos rígidos. Si no quitase la gravedad
de la escena, a los sólidos rígidos se les aplicaría la gravedad dos veces.

Por último, he puesto el límite a los generadores de entidades, por lo que tras un tiempo de
ejecución, los generadores dejan de generar entidades, excepto el de las explosiones (para 
enseñar que se pueden crear generadores sin ese límite)




