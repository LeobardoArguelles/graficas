import * as THREE from './node_modules/three/build/three.module.js';
////-------------------------
//// Cambiar la imagen de textura usando var teximage
////
////
////-------------------------

var ww = window.innerWidth,
  wh = window.innerHeight;

var renderer, camera, light, elements, geometry, material;
var box1, box2, box3;
var previousTime;
var sprite;

var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );
var materialDiffuse = vec4( 1.0, 0.8, 0.0, 1.0 );

function init() {

  renderer = new THREE.WebGLRenderer({
    canvas: document.getElementById('scene')
  });
  renderer.setClearColor(0xFFFFFF);
  renderer.setSize(ww, wh);

  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(50, ww / wh, 1, 10000);
  camera.position.set(0, 0, 700);
  scene.add(camera);

  light = new THREE.DirectionalLight(0xffffff, 1);
  light.position.set(0, 250, 700);
  scene.add(light);

  createBox();

  renderer.render(scene, camera);
  previousTime = Date.now();
  animate();
};

function createBox() {

  elements = new THREE.Object3D();

  //Create a geometry for a cube
  geometry = new THREE.BoxGeometry(200, 200, 200);

  //Create a Texture Loader object
  var loader = new THREE.TextureLoader();
  loader.crossOrigin = 'anonymous';
  var texture = loader.load("textura.jpg");

  diffuseProduct = mult(lightDiffuse, materialDiffuse);

  ////-------------------------
  //// Crear Box #1 cambiando la  
  //// imagen de textura.  
  //// Incluir iluminacion difusa
  ////-------------------------
  material = new THREE.MeshLambertMaterial({
    map: texture
  });
  box1 = new THREE.Mesh(geometry, material);
  box1.rotation.z = Math.PI / 8;
  box1.position.x = -340;
                        
  //Add it into our group
  elements.add(box1);

  ////-------------------------
  //// Crear Box #2 agregando color 
  //// en la función de textura
  ////-------------------------
  material = new THREE.MeshLambertMaterial({
    map: texture,
    color: 0xD8362A
  });
  box2 = new THREE.Mesh(geometry, material);
  box2.rotation.z = Math.PI / 8;
  box2.position.x = 100;
  elements.add(box2);
 


  ////-------------------------
  //// Crear Box #3 utilizando un
  //// modelo de iluminación diferente 
  //// al material difuso (ej. Phong)
  ////------------------------- 


  scene.add(elements);

};


var counter = 0;
var animate = function(a) {

  requestAnimationFrame(animate);
  box1.rotation.y += .01;
  box2.rotation.y += .01;


  var frameTime = Date.now();
  var delta = frameTime - previousTime;
  if (delta > 50) {
    previousTime = frameTime;
    sprite.offset.x = (counter % 4) / 4;
    sprite.offset.y = Math.floor(counter / 4) / 3;
    counter++;
    if (counter == 12) {
      counter = 0;
    }
  }

  renderer.render(scene, camera);
};

init();