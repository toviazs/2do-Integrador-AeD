# Segundo Trabajo Integrador

# Cátedra de Algoritmos y Estructuras de Datos

![UTN-FRT](https://upload.wikimedia.org/wikipedia/en/b/bd/UTN.png)

## Introducción

El siguiente trabajo consta del análisis y seguimiento del desarrollo de las consignas propuestas por la cátedra de Algoritmos y Estructuras de Datos, en un intento de integrar los diversos conocimientos adquiridos durante su cursado, por medio de la implementación de un conjunto de programas interconectados con menús y archivos de datos de acceso compartido.
El código aquí expuesto fue escrito tratando de cumplir con las buenas prácticas de la programación que se vieron durante el año. Además, su armado fue gestionado, controlado y compartido, por medio de la herramienta de control de versiones Git y la plataforma GitHub, siendo el uso de estas últimas facilitado por la colaboración de los mentores de la comunidad ProgramaConNosotros.

## Integrantes

Los colaboradores de este repositorio corresponden a alumnos de primer año de Ingeniería en Sistemas de Información de la UTN - FRT:

1. [Paz Posse Tobías](https://github.com/toviazs)
2. [Pérez Lucas Gustavo](https://github.com/lucasgp14)
3. [Paz Bruno Leonel](https://github.com/YaiZ-cpp)
4. [Posse Ricardo](https://github.com/RicardoPosse)

## Consigna

En este segundo trabajo integrador se desarrollará una aplicación que permita registrar las atenciones de las mascotas que asisten de un centro veterinario con múltiples consultorios de distintos profesionales. Deberá constar también de un módulo para la gestión de turnos y otro para la administración gerencial.

### Módulo Consultorio

Esta parte del proyecto estará dirigida a los diferentes profesionales que atienden y registran la evolución de las mascotas en una base de datos de historias clínicas. El sistema deberá contar con un listado de las mascotas que están registradas para ser atendidas ese día, para visualizarla, el veterinario deberá identificarse en el sistema por medio de su número de matrícula y contraseña y accediendo a la opción indicada. De esta manera el veterinario llamará por apellido y nombre a la mascotaque atenderá, una vez realizada esta tarea procede al ingreso de la evolución, en un texto de no más de 380 caracteres. Luego de realizada esta operación la mascota debe desaparecer del listado. Los datos de interés para el veterinario en este proceso son: Apellido y Nombres de la mascota (el apellido corresponde al dueño o familia), DNI del dueño, Localidad, Edad (calculada con la fecha de nacimiento registrada), y el Peso.
La historia clínica de la mascota es común para todos los veterinarios, por lo tanto se deberá visualizar fecha de atentación de la misma y el nombre del veterinario que la redacto.

### Módulo Recepción

Este módulo satisface las necesidades del personal que asiste a los veterinarios en la atención al público. Desde aquí se hace ingreso de las mascotas, y la registración de los turnos. Esta aplicación debe permitir obtener un informe de las mascotas atendidos en determinada fecha por un determinado veterinario.

### Módulo Administración

La gerencia del centro veterinario es la encargada de realizar el alta de los veterinarios que trabajan en la institución, así como también de los empleados que realizan la registración de los turnos y mascotas. Es el área encargada desea visualizar las atenciones realizadas por los profesionales según las en el mes.Para incentivar a los veterinarios, la gerencia otorga un bono mensual al profesional que haya registrado la mayor cantidad de turnos en ese periodo.
