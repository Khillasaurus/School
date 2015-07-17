package 
{
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	
	public class Main extends Sprite
	{
		public static var holder:Holder;
		public var galleryList;
		
		private var nextImg:uint = 1;

		public function Main()
		{
			holder = new Holder();
			addChild( holder );
			galleryList = new GalleryList();
			addChild( galleryList );
			
			stage.addEventListener( MouseEvent.CLICK, nextImage );
		}
		
		public function loadImage( img:String ):void
		{
			var imgLoad:Preloader = new Preloader(img);
			addChild(imgLoad);
		}
		
		private function nextImage( mb:MouseEvent):void
		{
			if( holder.numChildren > 0 )
			{
				loadImage( galleryList.galXML.theImage[nextImg].fileLoc.text());
				nextImg++;
				if( nextImg == galleryList.galXML.theImage.length() )
				{
					nextImg = 0;
				}
				holder.removeChildAt( 0 );
			}
		}

	}
	
}
