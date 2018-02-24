

Al añadir un nuevo proyecto recuerda añadir la página de propiedades ProyectosGLFG.props al nuevo proyecto:
Menú VER -> administrador de propiedades -> Agregar hoja de propiedades existente -> ProyectosGLFG.props -> Guardar

Para añadir una nueva libreria, copia su directorio en la solución y los bin de la libreria en el directorio bin de la solución.
Y añade los nuevos elementos al archivo ProyectosGLFG.props en las lineas: IncludePath, LibraryPath y AdditionalDependencies.
También puedes crear otras páginas de propiedades.