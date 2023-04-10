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
<section id="features"></section>

<!-- Guides and Documentation -->
<section id="docs" class="bg-gray-300">
	<h2>Guides:</h2>
	<h2>Documentation:</h2>
</section>

<!-- Contributing -->
<section id="contributing"></section>