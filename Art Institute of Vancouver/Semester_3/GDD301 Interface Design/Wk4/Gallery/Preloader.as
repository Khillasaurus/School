package 
{
	import flash.display.Sprite;
	import flash.display.Loader;
	import flash.display.LoaderInfo;
	import flash.events.Event;
	import flash.events.ProgressEvent;
	import flash.net.URLRequest;
	
	public class Preloader extends Sprite
	{
		private var targetLdr:LoaderInfo;
		private var percent:Number = 0;
		private var MyUrl:String;
			
		public function Preloader( newURL )
		{
			MyUrl = newURL;
			var loader:Loader = new Loader();
			targetLdr = loader.contentLoaderInfo;
			targetLdr.addEventListener( ProgressEvent.PROGRESS, loadingData );
			targetLdr.addEventListener( Event.COMPLETE, finishedLoading );
			loader.load( new URLRequest(MyUrl) );
		}
		
		private function loadingData( evt:ProgressEvent ):void
		{
			percent = targetLdr.bytesLoaded / targetLdr.bytesTotal;
			graphics.clear();
			graphics.beginFill( 0xFF0000 );
			graphics.drawRect( 0, 380, percent * 550, 20 );
			graphics.endFill();
		}
		
		private function finishedLoading( evt:Event ):void
		{
			graphics.clear();
			targetLdr.removeEventListener( ProgressEvent.PROGRESS, loadingData );
			targetLdr.removeEventListener( Event.COMPLETE, finishedLoading );
			Main.holder.addChild( targetLdr.content );
			parent.removeChild( this );
		}

	}
	
}
