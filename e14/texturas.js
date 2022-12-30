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
  geometry = new THREE.BoxGeometry(100, 100, 100);

  //Create a Texture Loader object
  var loader = new THREE.TextureLoader();
  loader.crossOrigin = 'anonymous';
  var texture = loader.load("texture.jpg");


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
  box1.position.x = -320;
                        
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
  box2.position.x = -100;
  elements.add(box2);

  material = new THREE.MeshPhongMaterial({
      map: texture
    });
  box3 = new THREE.Mesh(geometry, material);
  box3.rotation.z = Math.PI / 8;
  box3.position.x = 100;
  elements.add(box3);


  ////-------------------------
  //// Crear Box #3 utilizando un
  //// modelo de iluminación diferente 
  //// al material difuso (ej. Phong)
  ////------------------------- 


  const light = new THREE.AmbientLight( 0x404040 );
  scene.add( light );
  scene.add(elements);

};


var counter = 0;
var animate = function(a) {

  requestAnimationFrame(animate);
  box1.rotation.y += .01;
  box2.rotation.y += .01;
  box3.rotation.y += .01;


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
