import { defineConfig } from 'windicss/helpers';

export default defineConfig({
	theme: {
		fontFamily: {
			header: ['Poiret One'],
			body: [],
			code: []
		},
		extend: {
			colors: {
				'manilla-paper': '#F9EFD9',
				cardstock: '#BFA182',
				'sun-yellow': '#FFF38D',
				'canyon-orange': '#FF8D28',
				'mars-red': '#FF2D0D',
				'inky-black': '#2D2D2D',
				'marble-white': '#FEFAFE'
			}
		}
	}
});
