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

    for (let i = 0; i < divisions; i++) {
        var theta = degrees*i;
        console.log(cos(theta));
        pointsArray.push(r*cos(theta));
        pointsArray.push(r*sin(theta));
        pointsArray.push(0.0);
        indices.push(i);
    }
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

    cylinder(0.5, 0.5, 20);

    vBuffer = gl.createBuffer();

    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    idxBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ELEMENT_ARRAY_BUFFER, idxBuffer );
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);


    console.log(pointsArray);
    console.log(indices);
    gl.clear( gl.COLOR_BUFFER_BIT );
    gl.drawElements(gl.TRIANGLE_FAN, indices.length, gl.UNSIGNED_SHORT, 0);
}
