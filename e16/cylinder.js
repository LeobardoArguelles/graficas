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

function cylinder (radius = 0.5, height = 0.5, divisions = 4) {
    pointsArray = [
        -0.5, 0.5,
        0.5, -0.5,
        0.5, 0.5,
        -0.5, -0.5
    ];
    indices = [
        0, 2, 1, 0, 1, 3
    ];
}

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );



    program = initShaders( gl, "vertex-shader", "fragment-shader");

    gl.useProgram( program);

    // instanceMatrix = mat4();

    // projectionMatrix = ortho(-10.0,10.0,-10.0, 10.0,-10.0,10.0);
    // modelViewMatrix = mat4();


    // gl.uniformMatrix4fv(gl.getUniformLocation( program, "modelViewMatrix"), false, flatten(modelViewMatrix) );
    // gl.uniformMatrix4fv( gl.getUniformLocation( program, "projectionMatrix"), false, flatten(projectionMatrix) );

    // modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix")

    cylinder();

    vBuffer = gl.createBuffer();

    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    idxBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ELEMENT_ARRAY_BUFFER, idxBuffer );
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);


    gl.clear( gl.COLOR_BUFFER_BIT );
    // gl.drawArrays(gl.TRIANGLES, 0, 3);
    gl.drawElements(gl.TRIANGLES, 6, gl.UNSIGNED_SHORT, 0);
}
