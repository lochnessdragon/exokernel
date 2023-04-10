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
	<h2>Features</h2>
	<!-- Old OS work like x -->
	<!-- Our os works like this -->
	<!-- For users, this means -->
	<!-- For devs, this means -->
	<!-- For sysadmins, this means -->
</section>

<!-- Guides and Documentation -->
<section id="docs" class="bg-gray-900 text-white">
	<h2 class="font-bold text-4xl">Guides:</h2>
	<!-- Getting started -->
	<!-- How to write a lib os -->
	<!-- Compiling the project -->
	<h2 class="font-bold text-4xl">Documentation:</h2>
	<!-- API Documentation -->
</section>

<!-- Contributing -->
<section id="contributing" class="text-white bg-purple-900">
	<h2 class="font-bold text-4xl">Contributing:</h2>
	<!-- Contrib souce -->
	<!-- Code of Conduct -->
	<!-- Help Q&A -->
</section>