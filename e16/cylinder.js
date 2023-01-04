var canvas;
var gl;
var program;

var pointsArray = [];
var indices = [];

function quad(a, b, c, d) {
     pointsArray.push(vertices[a]);
     pointsArray.push(vertices[b]);
     pointsArray.push(vertices[c]);
     pointsArray.push(vertices[d]);
}

function cylinder (r = 0.5, height = 0.5, divisions = 4) {
    var degrees = 2*Math.PI / divisions
    var cos = Math.cos
    var sin = Math.sin
    var counter = 0;

    for (let i = 0; i < divisions; i++) {
        var theta = degrees*i;

        // TODO: Corregir, sólo funciona con division = 4
        if (counter == 0) {
            pointsArray.push(r*cos(theta));
            pointsArray.push(0.5);
            pointsArray.push(r*sin(theta));

            pointsArray.push(r*cos(theta));
            pointsArray.push(-0.5);
            pointsArray.push(r*sin(theta));

            indices.push(counter++);
            indices.push(counter++);
        }
        else if (counter == 2) {
            pointsArray.push(r*cos(theta));
            pointsArray.push(-0.5);
            pointsArray.push(r*sin(theta));

            pointsArray.push(r*cos(theta));
            pointsArray.push(0.5);
            pointsArray.push(r*sin(theta));

            indices.push(counter++);
            indices.push(counter++);
        }
        else if (counter < 5) {
            pointsArray.push(r*cos(theta));
            pointsArray.push(0.5);
            pointsArray.push(r*sin(theta));

            indices.push(counter++);
        }
        else {
            pointsArray.push(r*cos(theta));
            pointsArray.push(0.5);
            pointsArray.push(r*sin(theta));

            pointsArray.push(r*cos(theta));
            pointsArray.push(-0.5);
            pointsArray.push(r*sin(theta));

            indices.push(counter++);
            indices.push(counter++);
        }

    }
}

window.onload = function init() {
    const divisions = 4;

    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );



    program = initShaders( gl, "vertex-shader", "fragment-shader");

    gl.useProgram( program);

    modelViewMatrix = mat4();
    console.log(modelViewMatrix);
    modelViewMatrix = mult(modelViewMatrix, rotate(10, 1, 0, 0));
    projectionMatrix = ortho(-1.0,1.0,-1.0, 1.0,-1.0,1.0);

    // TODO: Construir el resto del cilindro
    // TODO: Sustituir poligonos cuadrados por cilindros en humanoide.js
    // TODO: Agregar esferas en las articulaciones en humanoide.js
    // TODO: Crear animaciones


    gl.uniformMatrix4fv(gl.getUniformLocation( program, "modelViewMatrix"), false, flatten(modelViewMatrix) );
    gl.uniformMatrix4fv( gl.getUniformLocation( program, "projectionMatrix"), false, flatten(projectionMatrix) );

    modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix")

    cylinder(0.5, 0.5, divisions);

    vBuffer = gl.createBuffer();

    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    idxBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ELEMENT_ARRAY_BUFFER, idxBuffer );
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);

    gl.clear( gl.COLOR_BUFFER_BIT );
    gl.drawElements(gl.TRIANGLE_FAN, indices.length, gl.UNSIGNED_SHORT, 0);
}
