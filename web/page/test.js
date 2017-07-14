function initTest() {
var menItm = `
	<tr><td width=1><input type=submit onclick="ShowHideEvent( 'Test' );" value="Test"></td><td>
	<div id=Example class="collapsible">
	<p>This is a RSSI graph</p>	
	</div>
	</td></tr>
`;
}

function mainticker()
{
        KickRSSIgraph();
        setTimeout( mainticker, 1000 );
}

function maininit()
{
        setTimeout( mainticker, 1000 );
}


function RSSIDataTicker()
{
        if( IsTabOpen('RSSIgraph') )
        {
                QueueOperation( "CM",  GotRSSIgraph );
        }
        //$( "#OScopePauseButton" ).css( "background-color", (is_oscilloscope_running&&!pause_oscilloscope)?"green":"red" );
}

function KickRSSIgraph()
{
        RSSIDataTicker();
}


function GotRSSIgraph(req,data)
{
	var mult = Number(document.getElementById('OSCMultIn').value);
        document.getElementById('OSCMultOut').innerHTML = mult;
        var canvas = document.getElementById('RSSIgraphCanvas');
        var ctx = canvas.getContext('2d');
        var h = canvas.height;
        var w = canvas.width;
        if( ctx.canvas.width != canvas.clientWidth )   ctx.canvas.width = canvas.clientWidth;
        if( ctx.canvas.height != canvas.clientHeight ) ctx.canvas.height = canvas.clientHeight;

        $( "#RSSIPauseButton" ).css( "background-color", "green" );
	var imageData = ctx.getImageData(1, 0, ctx.canvas.width-1, ctx.canvas.height);
	ctx.putImageData(imageData, 0, 0);
	ctx.clearRect(ctx.canvas.width-1, 0, 1, ctx.canvas.height);
        var secs = data.split( "\t" );
	//var samps = Number(secs[1]);
        var data = secs[1];
        var samp = parseInt( data,16 );
        //if( parseInt( data.substr(4,2), 16) > (parseInt( data.substr(6,2), 16))) //Try some triggering ....
        //{
        //ctx.clearRect( 0, 0, canvas.width, canvas.height );
        var x = 511;
        var y = ( samp / 100 ) * canvas.clientHeight;
        ctx.fillRect(x,y,1,1);
	var delayMillis = 100; //1 second
	setTimeout(function()
	{
  		RSSIDataTicker();	
	}, delayMillis);
}

window.addEventListener("load", initTest, false);

