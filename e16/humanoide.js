
var canvas;
var gl;
var program;

var projectionMatrix; 
var modelViewMatrix;

var instanceMatrix;

var modelViewMatrixLoc;

var vertices = [

    vec4( -0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5,  0.5,  0.5, 1.0 ),
    vec4( 0.5,  0.5,  0.5, 1.0 ),
    vec4( 0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5, -0.5, -0.5, 1.0 ),
    vec4( -0.5,  0.5, -0.5, 1.0 ),
    vec4( 0.5,  0.5, -0.5, 1.0 ),
    vec4( 0.5, -0.5, -0.5, 1.0 )
];

var turning = false;
var running = false;
var resetting = false;

var torsoId = 0;
var headId  = 1;
var head1Id = 1;
var head2Id = 10;
var leftUpperArmId = 2;
var leftLowerArmId = 3;
var rightUpperArmId = 4;
var rightLowerArmId = 5;
var leftUpperLegId = 6;
var leftLowerLegId = 7;
var rightUpperLegId = 8;
var rightLowerLegId = 9;


var torsoHeight = 5.0;
var torsoWidth = 1.0;
var upperArmHeight = 3.0;
var lowerArmHeight = 2.0;
var upperArmWidth  = 0.5;
var lowerArmWidth  = 0.5;
var upperLegWidth  = 0.5;
var lowerLegWidth  = 0.5;
var lowerLegHeight = 2.0;
var upperLegHeight = 3.0;
var headHeight = 1.5;
var headWidth = 1.0;

var numNodes = 10;
var numAngles = 11;
var angle = 0;

var theta = [0, 0, 0, 0, 0, 0, 180, 0, 180, 0, 0];
var starting_theta = theta.slice();

var numVertices = 24;

var stack = [];

var figure = [];

for( var i=0; i<numNodes; i++) figure[i] = createNode(null, null, null, null);

var vBuffer;
var modelViewLoc;

var pointsArray = [];

//-------------------------------------------

function scale4(a, b, c) {
   var result = mat4();
   result[0][0] = a;
   result[1][1] = b;
   result[2][2] = c;
   return result;
}

//--------------------------------------------


function createNode(transform, render, sibling, child){
    var node = {
    transform: transform,
    render: render,
    sibling: sibling,
    child: child,
    }
    return node;
}


function initNodes(Id) {

    var m = mat4();
    
    switch(Id) {
    
    case torsoId:
    
    m = rotate(theta[torsoId], 0, 1, 0 );
    figure[torsoId] = createNode( m, torso, null, headId );
    break;

    case headId: 
    case head1Id: 
    case head2Id:
    

    m = translate(0.0, torsoHeight+0.5*headHeight, 0.0);
	m = mult(m, rotate(theta[head1Id], 1, 0, 0))
	m = mult(m, rotate(theta[head2Id], 0, 1, 0));
    m = mult(m, translate(0.0, -0.5*headHeight, 0.0));
    figure[headId] = createNode( m, head, leftUpperArmId, null);
    break;
    
    
    case leftUpperArmId:
    
    m = translate(-(torsoWidth+upperArmWidth), 0.9*torsoHeight, 0.0);
	m = mult(m, rotate(theta[leftUpperArmId], 1, 0, 0));
    figure[leftUpperArmId] = createNode( m, leftUpperArm, rightUpperArmId, leftLowerArmId );
    break;

    case rightUpperArmId:
    
    m = translate(torsoWidth+upperArmWidth, 0.9*torsoHeight, 0.0);
	m = mult(m, rotate(theta[rightUpperArmId], 1, 0, 0));
    figure[rightUpperArmId] = createNode( m, rightUpperArm, leftUpperLegId, rightLowerArmId );
    break;
    
    case leftUpperLegId:
    
    m = translate(-(torsoWidth+upperLegWidth), 0.1*upperLegHeight, 0.0);
	m = mult(m , rotate(theta[leftUpperLegId], 1, 0, 0));
    figure[leftUpperLegId] = createNode( m, leftUpperLeg, rightUpperLegId, leftLowerLegId );
    break;

    case rightUpperLegId:
    
    m = translate(torsoWidth+upperLegWidth, 0.1*upperLegHeight, 0.0);
	m = mult(m, rotate(theta[rightUpperLegId], 1, 0, 0));
    figure[rightUpperLegId] = createNode( m, rightUpperLeg, null, rightLowerLegId );
    break;
    
    case leftLowerArmId:

    m = translate(0.0, upperArmHeight, 0.0);
    m = mult(m, rotate(theta[leftLowerArmId], 1, 0, 0));
    figure[leftLowerArmId] = createNode( m, leftLowerArm, null, null );
    break;
    
    case rightLowerArmId:

    m = translate(0.0, upperArmHeight, 0.0);
    m = mult(m, rotate(theta[rightLowerArmId], 1, 0, 0));
    figure[rightLowerArmId] = createNode( m, rightLowerArm, null, null );
    break;
    
    case leftLowerLegId:

    m = translate(0.0, upperLegHeight, 0.0);
    m = mult(m, rotate(theta[leftLowerLegId], 1, 0, 0));
    figure[leftLowerLegId] = createNode( m, leftLowerLeg, null, null );
    break;
    
    case rightLowerLegId:

    m = translate(0.0, upperLegHeight, 0.0);
    m = mult(m, rotate(theta[rightLowerLegId], 1, 0, 0));
    figure[rightLowerLegId] = createNode( m, rightLowerLeg, null, null );
    break;
    
    }

}

function traverse(Id) {
   
   if(Id == null) return; 
   stack.push(modelViewMatrix);
   modelViewMatrix = mult(modelViewMatrix, figure[Id].transform);
   figure[Id].render();
   if(figure[Id].child != null) traverse(figure[Id].child); 
    modelViewMatrix = stack.pop();
   if(figure[Id].sibling != null) traverse(figure[Id].sibling); 
}

function torso() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5*torsoHeight, 0.0) );
    instanceMatrix = mult(instanceMatrix, scale4( torsoWidth, torsoHeight, torsoWidth));
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function head() {
   
    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * headHeight, 0.0 ));
	instanceMatrix = mult(instanceMatrix, scale4(headWidth, headHeight, headWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function leftUpperArm() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * upperArmHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(upperArmWidth, upperArmHeight, upperArmWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function leftLowerArm() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * lowerArmHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(lowerArmWidth, lowerArmHeight, lowerArmWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function rightUpperArm() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * upperArmHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(upperArmWidth, upperArmHeight, upperArmWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function rightLowerArm() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * lowerArmHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(lowerArmWidth, lowerArmHeight, lowerArmWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function  leftUpperLeg() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * upperLegHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(upperLegWidth, upperLegHeight, upperLegWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function leftLowerLeg() {
    
    instanceMatrix = mult(modelViewMatrix, translate( 0.0, 0.5 * lowerLegHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(lowerLegWidth, lowerLegHeight, lowerLegWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function rightUpperLeg() {
    
    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * upperLegHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(upperLegWidth, upperLegHeight, upperLegWidth) );
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function rightLowerLeg() {

    instanceMatrix = mult(modelViewMatrix, translate(0.0, 0.5 * lowerLegHeight, 0.0) );
	instanceMatrix = mult(instanceMatrix, scale4(lowerLegWidth, lowerLegHeight, lowerLegWidth) )
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(instanceMatrix));
    for(var i =0; i<6; i++) gl.drawArrays(gl.TRIANGLE_FAN, 4*i, 4);
}

function quad(a, b, c, d) {
     pointsArray.push(vertices[a]); 
     pointsArray.push(vertices[b]); 
     pointsArray.push(vertices[c]);     
     pointsArray.push(vertices[d]);    
}

// function cylinder (r = 0.5, height = 0.5, divisions = 4) {
//     var degrees = 2*Math.PI / divisions
//     var cos = Math.cos
//     var sin = Math.sin
//     var counter = 0;

//     for (let i = 0; i < divisions; i++) {
//         var theta = degrees*i;

//         // TODO: Corregir, s??lo funciona con division = 4
//         if (counter == 0) {
//             pointsArray.push(r*cos(theta));
//             pointsArray.push(0.5);
//             pointsArray.push(r*sin(theta));

//             pointsArray.push(r*cos(theta));
//             pointsArray.push(-0.5);
//             pointsArray.push(r*sin(theta));

//             indices.push(counter++);
//             indices.push(counter++);
//         }
//         else if (counter == 2) {
//             pointsArray.push(r*cos(theta));
//             pointsArray.push(-0.5);
//             pointsArray.push(r*sin(theta));

//             pointsArray.push(r*cos(theta));
//             pointsArray.push(0.5);
//             pointsArray.push(r*sin(theta));

//             indices.push(counter++);
//             indices.push(counter++);
//         }
//         else if (counter < 5) {
//             pointsArray.push(r*cos(theta));
//             pointsArray.push(0.5);
//             pointsArray.push(r*sin(theta));

//             indices.push(counter++);
//         }
//         else {
//             pointsArray.push(r*cos(theta));
//             pointsArray.push(0.5);
//             pointsArray.push(r*sin(theta));

//             pointsArray.push(r*cos(theta));
//             pointsArray.push(-0.5);
//             pointsArray.push(r*sin(theta));

//             indices.push(counter++);
//             indices.push(counter++);
//         }

//     }
// }



function cube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}


window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
    
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    
    //
    //  Load shaders and initialize attribute buffers
    //
    program = initShaders( gl, "vertex-shader", "fragment-shader");
    
    gl.useProgram( program);

    instanceMatrix = mat4();
    
    projectionMatrix = ortho(-10.0,10.0,-10.0, 10.0,-10.0,10.0);
    modelViewMatrix = mat4();

        
    gl.uniformMatrix4fv(gl.getUniformLocation( program, "modelViewMatrix"), false, flatten(modelViewMatrix) );
    gl.uniformMatrix4fv( gl.getUniformLocation( program, "projectionMatrix"), false, flatten(projectionMatrix) );
    
    modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix")
    
    cube();
        
    vBuffer = gl.createBuffer();
        
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);
    
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );
    
        document.getElementById("slider0").onchange = function() {
        theta[torsoId ] = parseInt(event.srcElement.value);
        initNodes(torsoId);
    };
        document.getElementById("slider1").onchange = function() {
        theta[head1Id] = parseInt(event.srcElement.value);
        initNodes(head1Id);
    };

    document.getElementById("slider2").onchange = function() {
         theta[leftUpperArmId] = parseInt(event.srcElement.value);
         initNodes(leftUpperArmId);
    };
    document.getElementById("slider3").onchange = function() {
         theta[leftLowerArmId] =  parseInt(event.srcElement.value);
         initNodes(leftLowerArmId);
    };
     
        document.getElementById("slider4").onchange = function() {
        theta[rightUpperArmId] = parseInt(event.srcElement.value);
        initNodes(rightUpperArmId);
    };
    document.getElementById("slider5").onchange = function() {
         theta[rightLowerArmId] =  parseInt(event.srcElement.value);
         initNodes(rightLowerArmId);
    };
        document.getElementById("slider6").onchange = function() {
        theta[leftUpperLegId] = parseInt(event.srcElement.value);
        initNodes(leftUpperLegId);
    };
    document.getElementById("slider7").onchange = function() {
         theta[leftLowerLegId] = parseInt(event.srcElement.value);
         initNodes(leftLowerLegId);
    };
    document.getElementById("slider8").onchange = function() {
         theta[rightUpperLegId] =  parseInt(event.srcElement.value);
         initNodes(rightUpperLegId);
    };
        document.getElementById("slider9").onchange = function() {
        theta[rightLowerLegId] = parseInt(event.srcElement.value);
        initNodes(rightLowerLegId);
    };
    document.getElementById("slider10").onchange = function() {
         theta[head2Id] = parseInt(event.srcElement.value);
         initNodes(head2Id);
    };
    document.getElementById("rotate-btn").onclick = startTurning;
    document.getElementById("run-btn").onclick = startRunning;

    for(i=0; i<numNodes; i++) initNodes(i);
    
    render();
}

var render = function() {

        gl.clear( gl.COLOR_BUFFER_BIT );
        traverse(torsoId);
        requestAnimFrame(render);
}

// ANIMACIONES
function startTurning() {
    if (turning) resetting = true;
    turning = !turning;
    turn();
    // if (resetting) {
    //     reset();
    // }
}

async function startRunning() {
    if (running) resetting = true;
    running = !running;
    // await ready();
    if (running) {
        await getSet();
        run();
    }
}

async function reset() {
    var done = new Array(theta.length).fill(false);
    while (!done.every(el => el === true)) {
        for (var i = 0; i < theta.length; i++) {
            if (!done[i] && starting_theta[i] != theta[i]) {
                var target_val = starting_theta[i]
                var theta_val = theta[i]
                if (( target_val - theta_val ) < 0) {
                    theta[i] -= 1;
                }
                else {
                    theta[i] += 1;
                }

                console.log(i + ": " + theta[i] + " || " + starting_theta[i]);
                initNodes(i);
                traverse(torsoId);
                if (!resetting) break;
            }
            else done[i] = true;
        }
        await sleep(1);
    }
    resetting = false;
}

var ready = reset;

async function getSet() {
    var target = [140, 180, -70, 220, -70, 190, 60, 150, 70]
    var done = new Array(target.length).fill(false);
    var idxs = [0]
    for (var i = 2; i <= 9; i++) {
        idxs.push(i);
    }

    while (!done.every(el => el === true)) {
        for (var i = 0; i < target.length; i++) {
            var idx = idxs[i];
            if (!done[i] && target[i] != theta[idx]) {
                var target_val = target[i]
                var theta_val = theta[idx]
                if (target_val - theta_val <= 0) {
                    theta[idx] -= 1;
                }
                else {
                    theta[idx] += 1;
                }
                initNodes(idx);
            }
            else done[i] = true;
        }
        await sleep(1);
    }
}

async function moveArms(direction = 0) {
    var targets = [[140, 180, 150, 190], [180, 140, 190, 150]]
    var target = targets[direction]
    var done = new Array(target.length).fill(false);
    var idxs = [2, 4, 6, 8]

    while (!done.every(el => el === true)) {
        for (var i = 0; i < target.length; i++) {
            var idx = idxs[i];
            if (!done[i] && target[i] != theta[idx]) {
                var target_val = target[i]
                var theta_val = theta[idx]
                if (target_val - theta_val <= 0) {
                    theta[idx] -= 1;
                }
                else {
                    theta[idx] += 1;
                }
                initNodes(idx);
            }
            else done[i] = true;
        }
        await sleep(1);
    }
    return (direction == 1 ? 0 : 1)
}

async function moveLegs(direction = 0) {
    var targets = [[150, 190], [190, 150]]
    var target = targets[direction]
    var done = new Array(target.length).fill(false);
    var idxs = [2, 4]

    while (!done.every(el => el === true)) {
        for (var i = 0; i < target.length; i++) {
            var idx = idxs[i];
            if (!done[i] && target[i] != theta[idx]) {
                var target_val = target[i]
                var theta_val = theta[idx]
                if (target_val - theta_val <= 0) {
                    theta[idx] -= 1;
                }
                else {
                    theta[idx] += 1;
                }
                initNodes(idx);
                traverse(torsoId);
            }
            else done[i] = true;
        }
        await sleep(1);
    }
    return (direction == 1 ? 0 : 1)
}

async function run(direction = 0) {
    if (running) {
        direction = await moveArms(direction);
        // moveLegs();
        run(direction);
    }
}

async function turn() {
    if (turning) {
        resetting = false;
        if (theta[torsoId] >= 360) theta[torsoId] = 0;
        theta[torsoId] += 5;
        initNodes(torsoId);
        await sleep(10);
        turn();
    }
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
