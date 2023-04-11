<script>
	import welcome from '$lib/images/svelte-welcome.webp';
	import welcome_fallback from '$lib/images/svelte-welcome.png';
	import feather from 'feather-icons';
</script>

<svelte:head>
	<title>Exokernel</title>
	<meta name="description" content="Let's reshape how we think about computers." />
</svelte:head>

<!-- Download/header -->
<section id="banner">
	<div class="text-left min-h-screen">
		<h1 class="text-5xl mb-4">
			Exokernel
		</h1>
		<div class="justify-center">
			<button class="hover:bg-rainbow inline-svg rounded-md py-2 px-6 text-center bg-green-400">Download .iso {@html feather.icons.download.toSvg({'width': 18, 'height': 18})}</button>
			<p class="text-slate-700">Latest Version: <span class="underline">v0.0.1</span></p>
		</div>
	</div>
</section>

<!-- Features -->
<section id="features">
	<h2 class="font-bold text-4xl md:text-6xl">Features</h2>
	<!-- Old OS work like x -->
	<!-- Our os works like this -->
	<!-- For users, this means -->
	<!-- For devs, this means -->
	<!-- For sysadmins, this means -->
</section>

<!-- Guides and Documentation -->
<section id="docs" class="bg-gray-900 text-white pt-4 p-1">
	<h2 class="font-bold text-4xl md:text-6xl">Guides:</h2>
	<!-- Getting started -->
	<!-- How to write a lib os -->
	<!-- Compiling the project -->
	<p>In order to start your journey into the stars, I suggest <a class="underline"><i>The Beginner's Guide by R. U. Reddy</i></a>. If you are a developer looking to compile the project, there's is no better guide than <a class="underline"><i>Birthing your own Exokernel by Bertha Pangs</i></a>. Finally, if you are looking to grow your own library operating system, check out <a class="underline"><i>Cultivating a healthy Library (OS) by Chist M. Dev</i></a>.</p>
	<h2 class="font-bold text-4xl md:text-6xl">Documentation:</h2>
	<!-- API Documentation -->
	<p>Fuddled over functions? Mixed up by methods? Lacking a general sense of direction through the forest of knowledge? Maybe the <a class="underline">Definitely Definitive Dive into the API</a> will help.</p>
</section>

<!-- Contributing -->
<section id="contributing" class="text-white bg-purple-900 pt-4 p-1 text-left">
	<h2 class="font-bold text-4xl md:text-6xl">Contributing:</h2>
	<!-- Contrib souce -->
	<!-- Code of Conduct -->
	<!-- Help Q&A -->
	<p>All development of the code happens on Github. Make sure to read the Code of Conduct when interacting with the community. Also, if you need help, check out the Q&A discussions.</p>
</section>